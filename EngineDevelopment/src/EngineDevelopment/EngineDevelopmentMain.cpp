#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <unordered_map>

#include <ArchiveParser/ArchiveReader.h>
#include <ArchiveParser/XmlReader.h>

namespace fs = std::filesystem;

struct Counter
{
	size_t Min = (size_t)-1;
	size_t Max = 0;

	Counter& operator=(size_t value)
	{
		Min = std::min(Min, value);
		Max = std::max(Max, value);

		return *this;
	}

	void print(const std::string& name)
	{
		std::cout << name << " min: " << Min << std::endl;
		std::cout << name << " max: " << Max << std::endl;
	}
};

struct AttributeData
{
	std::vector<std::unordered_set<std::string>> AttributeSets;
	std::unordered_set<std::string> ChildNodes;
	std::unordered_set<std::string> ChildConditions;
	bool CanHaveAiPreset = false;
	bool IsTopLevel = false;
	std::string Name;
};

struct Parser
{
	bool Verbose = false;
	Archive::ArchiveReader::Path SubPath;
	XmlLite::XmlReader Document;

	std::unordered_set<std::string> rootChildren;
	std::unordered_set<std::string> battleChildren;
	std::unordered_map<std::string, AttributeData> battle_nodeData;
	std::unordered_set<std::string> reservedChildren;
	std::unordered_map<std::string, AttributeData> reserved_conditionData;
	std::unordered_set<std::string> battleEndChildren;
	std::unordered_map<std::string, AttributeData> battleEnd_nodeData;
	std::unordered_set<std::string> aiPresetsChildren;
	std::unordered_map<std::string, AttributeData> aiPresets_aiPresetData;
	std::unordered_set<std::string> aiPresets_aiPresetNames;

	std::unordered_map<std::string, AttributeData> nodeTypes;
	std::unordered_map<std::string, AttributeData> conditionTypes;
};

void printPath(Parser& parser)
{
	if (parser.Verbose)
	{
		std::cout << parser.Document.GetFullNodePath() << std::endl;
		int i = 0;
		++i;
	}
}

void parseChild(Parser& parser, const XmlLite::XmlNode* childNode, AttributeData& parentData, const char* ancestorType, bool& unknownValueFound)
{
	printPath(parser);

	std::string childType = std::string(childNode->Name);
	std::string name;
	std::string childName;
	std::vector<std::string> attributes;
	bool foundName = false;
	
	parentData.CanHaveAiPreset |= childType == "aiPreset";

	if (childType != "aiPreset" && childType != "node" && childType != "condition")
	{
		std::cout << "node type '" << childType << "' found in '" << parentData.Name;
		
		if (!parentData.IsTopLevel)
		{
			std::cout << "' under npcAi." << ancestorType;
		}

		std::cout << std::endl;

		unknownValueFound = true;

		return;
	}

	for (const XmlLite::XmlAttribute* attribute = parser.Document.GetNextAttribute(); attribute; attribute = parser.Document.GetNextAttribute())
	{
		if (strncmp(attribute->Name.data(), "name", attribute->Name.size()) != 0)
		{
			if (!foundName)
			{
				std::cout << "node '" << childType << "' has attribute '" << attribute->Name << "' before 'name' under " << ancestorType << std::endl;
				unknownValueFound = true;

				continue;
			}

			if (childType == "aiPreset")
			{
				std::cout << "node '" << childType << "' has attribute '" << attribute->Name << "' under " << ancestorType << std::endl;
				unknownValueFound = true;

				continue;
			}

			attributes.push_back(std::string(attribute->Name));

			continue;
		}

		name = std::string(attribute->Value);
		childName = childType + "[" + name + "]";
		foundName = true;

		if (childType == "node" || childType == "condition")
		{
			auto& children = childType == "node" ? parentData.ChildNodes : parentData.ChildConditions;

			if (!children.contains(name))
			{
				std::cout << parentData.Name << " has child '" << childName << "'";

				if (!parentData.IsTopLevel)
				{
					std::cout << " in " << "npcAi." << ancestorType;
				}

				std::cout << std::endl;

				children.insert(name);

				unknownValueFound = true;
			}
		}
	}

	if (attributes.size() && (childType == "node" || childType == "condition"))
	{
		AttributeData& data = childType == "node" ? parser.nodeTypes[name] : parser.conditionTypes[name];

		bool foundMatching = false;
		auto& attributeSets = data.AttributeSets;

		for (const auto& set : attributeSets)
		{
			if (set.size() != attributes.size()) continue;

			foundMatching = true;

			for (const auto& attribute : attributes)
			{
				if (!set.contains(attribute))
				{
					foundMatching = false;

					break;
				}
			}

			if (foundMatching)
			{
				break;
			}
		}

		if (!foundMatching)
		{
			attributeSets.push_back({});

			for (const auto& attribute : attributes)
			{
				if (!attributeSets.back().contains(attribute))
				{
					attributeSets.back().insert(attribute);
				}
			}
		}
	}

	XmlLite::XmlReader::StackMarker childMarker = parser.Document.GetStackMarker();

	for (const XmlLite::XmlNode* subNode = parser.Document.GetFirstChild(); subNode; subNode = parser.Document.GetNextSibling(childMarker))
	{
		if (childType == "aiPreset")
		{
			std::cout << "node '" << childType << "' has child '" << subNode->Name << "' under " << ancestorType << std::endl;
			unknownValueFound = true;

			continue;
		}

		AttributeData& data = childType == "node" ? parser.nodeTypes[name] : parser.conditionTypes[name];

		data.Name = childName;

		parseChild(parser, subNode, data, ancestorType, unknownValueFound);
	}
}

/*
<npcAi>
	<reserved?>
		<condition[]? name="hpLess"> </condition>

		<condition name="hpLess" value=>
	</reserved>
	<battle?>
		<node[] name="jump,select,standby,skill,RemoveMe,conditions"> </node>

		<node name="jump" pos= speed= heightMultiplier= />
		<node name="select" prob= | useNpcProb=>
		<node name="standby" limit= animation=? cooltime=? (facePos=? | faceTarget=?) initialCooltime=? isKeepBattle=?>
		<node name="skill" idx= (facePos=? | faceTarget=?) initialCooltime=? isKeepBattle=?>
		<node name="RemoveMe" />
		<node name="conditions">
	</battle>
	<battleEnd?>
		<node[] name="HideVibrateAll,TriggerSetUserValue,SetMasterValue,summon,select,say,sidePopup,SetValueRangeTarget,TriggerModifyUserValue,runaway,CreateRandomRoom,CreateInteractObject,RemoveMe,conditions"?> </node>

		<node name="HideVibrateAll" isKeepBattle= >
		<node name="TriggerSetUserValue" key= value= triggerID= isKeepBattle=? >
		<node name="SetMasterValue" key= value= isModify=? >
		<node name="summon" npcId= npcCount= npcCountMax= delayTick=? lifeTime=? group= summonPosOffset=? summonRot=? master=? isKeepBattle=? >
		<node name="select" prob= >
		<node name="buff" type= id= />
		<node name="say" message= durationTick= delayTick=? isKeepBattle=? >
		<node name="sidePopup" duration= type= illust= script= >
		<node name="SetValueRangeTarget" key= value= radius= height=? isModify=? >
		<node name="TriggerModifyUserValue" key= value= triggerID= />
		<node name="runaway" till= limit= />
		<node name="CreateRandomRoom" randomRoomID= portalDuration= />
		<node name="CreateInteractObject" normal= interactID= lifeTime= kfmName= reactable= />
		<node name="RemoveMe" />
		<node name="conditions" >
			<condition />
		</node>
	</battleEnd>
	<aiPresets?>
		<aiPreset[] name="unique values">
	</aiPresets>
</npcAi>

<node>
	<node name="trace,skill,teleport,standby,setData,target,say,SetValue,conditions,jump,select,move,summon,HideVibrateAll,TriggerSetUserValue,ride,SetSlaveValue,SetMasterValue,runaway,MinimumHp,buff,TargetEffect,ShowVibrate,sidePopup,SetValueRangeTarget,announce,ModifyRoomTime,TriggerModifyUserValue,Buff,RemoveSlaves,CreateRandomRoom,CreateInteractObject" />

	<node name="trace" limit= skillIdx=? animation=? speed=? till=? initialCooltime=? cooltime=? isKeepBattle=? >
	<node name="skill" idx= level=? prob=? sequence=? facePos=? [zp]?faceTarget=? faceTargetTick=? initialCooltime=? c?ooltime=? limit=? rob=? isKeepBattle=? >
	<node name="teleport" pos= prob=? facePos=? faceTarget=? initialCooltime=? cooltime=? isKeepBattle=? >
	<node name="standby" limit= pro[pb]=? animation=? facePos=? faceTarget=? initialCooltime=? cooltime=? isKeepBattle=? >
	<node name="setData" key= value= cooltime=? >
	<node name="target" type= prob=? rank=? additionalId=? additionalLevel=? from=? to=? center=? target=? noChangeWhenNoTarget=? initialCooltime=? cooltime=? rob=? isKeepBattle=? >
	<node name="say" message= prob=? durationTick= delayTick=? initialCooltime=? cooltime=? isKeepBattle=? >
	<node name="SetValue" key= value= initialCooltime=? cooltime=? isModify=? isKeepBattle=? >
	<node name="conditions" initialCooltime=? cooltime=? isKeepBattle=? >
		<condition />
	</node>
	<node name="jump" pos= speed= heightMultiplier= type=? cooltime=? isKeepBattle=? >
	<node name="select" prob= | useNpcProb= >
	<node name="move" destination= prob=? animation=? limit=? speed=? faceTarget=? initialCooltime=? cooltime=? isKeepBattle=? >
	<node name="summon" npcId= npcCountMax= npcCount= delayTick=? lifeTime=? summonRot=? summonPos=? summonPosOffset=? summonTargetOffset=? summonRadius=? group=? master=? option=? cooltime=? isKeepBattle=? >
	<node name="HideVibrateAll" isKeepBattle= >
	<node name="TriggerSetUserValue" triggerID= key= value= cooltime=? isKeepBattle=? >
	<node name="ride" type= isRideOff= rideNpcIDs=? />
	<node name="SetSlaveValue" key= value= isRandom=? cooltime=? isModify=? isKeepBattle=? >
	<node name="SetMasterValue" key= value= isRandom=? cooltime=? isModify=? isKeepBattle=? >
	<node name="runaway" animation=? skillIdx=? till=? limit=? facePos=? initialCooltime=? cooltime=? >
	<node name="MinimumHp" hpPercent= />
	<node name="buff" id= type= level=? prob=? initialCooltime=? cooltime=? isTarget=? isKeepBattle=? >
	<node name="TargetEffect" effectName= >
	<node name="ShowVibrate" groupID= >
	<node name="sidePopup" type= illust= duration= script=? sound=? voice=? />
	<node name="SetValueRangeTarget" key= value= height=? radius=? cooltime=? isModify=? isKeepBattle=? >
	<node name="announce" message= durationTick= cooltime=? >
	<node name="ModifyRoomTime" timeTick= isShowEffect=? >
	<node name="TriggerModifyUserValue" triggerID= key= value= >
	<node name="Buff" id= level= type= />
	<node name="RemoveSlaves" isKeepBattle= >
	<node name="CreateRandomRoom" randomRoomID= portalDuration= />
	<node name="CreateInteractObject" normal= interactID= lifeTime= kfmName= reactable= />
	<node name="RemoveMe" >
	<node name="Suicide" >
</node>

<condition>
	<condition name="distanceOver,combatTime,distanceLess,skillRange,extraData,SlaveCount,hpOver,state,additional,feature,hpLess,DistanceLess,slaveCount,true," />

	<condition name="distanceOver" value= >
	<condition name="combatTime" battleTimeBegin= battleTimeLoop= battleTimeEnd=? >
	<condition name="distanceLess" value= >
	<condition name="skillRange" skillIdx= skillLev=? isKeepBattle=? >
	<condition name="extraData" key= value= op=? isKeepBattle=? >
	<condition name="SlaveCount" count= useSummonGroup=? summonGroup=? >
	<condition name="hpOver" value= >
	<condition name="state" targetState= >
	<condition name="additional" id= level=? overlapCount=? isTarget=? >
	<condition name="feature" feature= >
	<condition name="hpLess" value= >
	<condition name="DistanceLess" value= >
	<condition name="slaveCount" slaveCount= slaveCountOp= >
	<condition name="true" >
</condition>
*/
/*
npcAi.battle children: node,
npcAi.reserved children: condition,
npcAi.battleEnd children: node,
npcAi.aiPresets children: aiPreset,

npcAi.battle.node.name values with attributes: jump, select, standby, skill,
npcAi.battle.node.name="jump" attribute sets:
		pos, speed, heightMultiplier,
npcAi.battle.node.name="select" attribute sets:
		prob,
		useNpcProb,
npcAi.battle.node.name="standby" attribute sets:
		limit, faceTarget, isKeepBattle,
		limit, faceTarget,
		limit, cooltime, faceTarget, isKeepBattle,
		limit, faceTarget, cooltime,
		limit, isKeepBattle,
		limit, cooltime, faceTarget, initialCooltime,
		limit, faceTarget, animation, isKeepBattle,
		limit, faceTarget, animation,
		limit, facePos,
		limit, facePos, animation,
		limit, facePos, isKeepBattle,
		limit, faceTarget, initialCooltime,
		limit,
npcAi.battle.node.name="skill" attribute sets:
		idx,
		facePos, idx,
		isKeepBattle, idx,
		initialCooltime, facePos, idx,
		faceTarget, idx,
		facePos, cooltime, isKeepBattle, idx,
		facePos, isKeepBattle, idx,
npcAi.battle.node.name values with no attributes: RemoveMe, conditions,
npcAi.battle.node[select] can have child 'aiPreset' nodes
npcAi.battle.node[select] child 'node' types: trace, skill, standby, conditions, SetValue, target, buff, select, move, runaway, SetSlaveValue,
npcAi.battle.node[conditions] child 'condition' types: extraData, true, skillRange, additional, hpOver, combatTime, hpLess, state,
npcAi.battle.node[standby] child 'node' types: say, standby, teleport, skill, select, jump, TriggerSetUserValue, RemoveMe, buff, summon, move, target, SetValueRangeTarget, trace,
npcAi.battle.node[skill] child 'node' types: skill, standby, sidePopup, target, jump,

npcAi.reserved.condition.name values with attributes: hpLess,
npcAi.reserved.condition.name="hpLess" attribute sets:
		value,
npcAi.reserved.condition[hpLess] can have child 'aiPreset' nodes
npcAi.reserved.condition[hpLess] child 'node' types: SetMasterValue, skill, teleport, standby, say, SetValue, conditions, RemoveMe, TriggerSetUserValue, MinimumHp, buff, target, summon, SetSlaveValue, TriggerModifyUserValue, move, jump, select, trace,

npcAi.battleEnd.node.name values with attributes: TriggerSetUserValue, HideVibrateAll, buff, SetMasterValue, summon, select, sidePopup, SetValueRangeTarget, say, TriggerModifyUserValue, runaway, CreateRandomRoom, CreateInteractObject,
npcAi.battleEnd.node.name="TriggerSetUserValue" attribute sets:
		triggerID, key, value,
		value, isKeepBattle, triggerID, key,
npcAi.battleEnd.node.name="HideVibrateAll" attribute sets:
		isKeepBattle,
npcAi.battleEnd.node.name="buff" attribute sets:
		type, id,
npcAi.battleEnd.node.name="SetMasterValue" attribute sets:
		key, value,
		key, value, isModify,
npcAi.battleEnd.node.name="summon" attribute sets:
		npcId, npcCountMax, npcCount, group, summonRot, summonPosOffset, master,
		npcId, delayTick, npcCount, npcCountMax, group, master, summonPosOffset, summonRot,
		npcId, npcCountMax, npcCount, group, summonRot, master, lifeTime, summonPos,
		delayTick, npcId, npcCountMax, npcCount, group, summonRot, summonPosOffset, master, isKeepBattle,
		npcId, npcCountMax, npcCount, group, summonRot, summonPosOffset,
npcAi.battleEnd.node.name="select" attribute sets:
		prob,
npcAi.battleEnd.node.name="sidePopup" attribute sets:
		duration, type, illust, script,
npcAi.battleEnd.node.name="SetValueRangeTarget" attribute sets:
		key, value, radius, isModify,
		key, height, value, radius,
		key, value, height, radius, isModify,
		key, value, radius,
npcAi.battleEnd.node.name="say" attribute sets:
		durationTick, message, isKeepBattle,
		message, durationTick,
		durationTick, message, delayTick,
npcAi.battleEnd.node.name="TriggerModifyUserValue" attribute sets:
		triggerID, key, value,
npcAi.battleEnd.node.name="runaway" attribute sets:
		till, limit,
npcAi.battleEnd.node.name="CreateRandomRoom" attribute sets:
		randomRoomID, portalDuration,
npcAi.battleEnd.node.name="CreateInteractObject" attribute sets:
		normal, interactID, lifeTime, kfmName, reactable,
npcAi.battleEnd.node.name values with no attributes: RemoveMe, conditions,
npcAi.battleEnd.node[TriggerSetUserValue] child 'node' types: SetValueRangeTarget, conditions, TriggerModifyUserValue, TriggerSetUserValue,
npcAi.battleEnd.node[HideVibrateAll] child 'node' types: SetValueRangeTarget, say,
npcAi.battleEnd.node[conditions] child 'condition' types: extraData, true,
npcAi.battleEnd.node[SetMasterValue] child 'node' types: SetMasterValue, SetValueRangeTarget,
npcAi.battleEnd.node[summon] child 'node' types: conditions, TriggerSetUserValue, SetValueRangeTarget,
npcAi.battleEnd.node[select] child 'node' types: summon, setData, say, TriggerSetUserValue,
npcAi.battleEnd.node[SetValueRangeTarget] child 'node' types: SetValueRangeTarget, conditions,
npcAi.battleEnd.node[say] child 'node' types: TriggerSetUserValue,
npcAi.battleEnd.node[TriggerModifyUserValue] child 'node' types: TriggerSetUserValue,

npcAi.aiPresets.aiPreset.name values with no attributes: misc...,
npcAi.aiPresets.aiPreset[misc...] can have child 'aiPreset' nodes
npcAi.aiPresets.aiPreset[misc...] child 'node' types: MinimumHp, TriggerSetUserValue, conditions, standby, teleport, skill, select, target, Suicide, move, SetValue, buff,

node.name values with attributes: trace, skill, teleport, standby, setData, target, say, SetValue, conditions, jump, select, move, summon, TriggerSetUserValue, ride, SetSlaveValue, SetMasterValue, runaway, MinimumHp, buff, TargetEffect, ShowVibrate, sidePopup, SetValueRangeTarget, announce, ModifyRoomTime, TriggerModifyUserValue, Buff, RemoveSlaves, CreateInteractObject,
node.name="trace" attribute sets:
		limit, skillIdx,
		limit, animation, skillIdx,
		till, limit,
		limit, cooltime, skillIdx,
		till, limit, cooltime, initialCooltime,
		limit, animation, isKeepBattle, skillIdx,
		till, limit, cooltime,
		limit, till, animation,
		limit, till, speed,
		limit, cooltime, initialCooltime, skillIdx,
		limit, isKeepBattle, skillIdx,
		limit, initialCooltime, skillIdx,
		skillIdx,
		cooltime, skillIdx,
		limit, cooltime, animation, skillIdx,
		limit, animation, initialCooltime, skillIdx,
node.name="skill" attribute sets:
		idx,
		faceTarget, idx,
		c?ooltime, idx,
		cooltime, initialCooltime, idx,
		faceTarget, cooltime, idx,
		faceTarget, isKeepBattle, idx,
		cooltime, faceTarget, isKeepBattle, idx,
		isKeepBattle, idx,
		c?ooltime, isKeepBattle, idx,
		facePos, cooltime, isKeepBattle, idx,
		facePos, isKeepBattle, idx,
		facePos, idx,
		idx, level,
		cooltime, initialCooltime, facePos, isKeepBattle, idx,
		facePos, prob, isKeepBattle, idx,
		facePos, cooltime, idx,
		prob, idx,
		prob, facePos, idx,
		faceTarget, prob, idx,
		faceTarget, cooltime, initialCooltime, idx,
		faceTarget, initialCooltime, idx,
		faceTarget, cooltime, initialCooltime, isKeepBattle, idx,
		faceTarget, facePos, idx,
		cooltime, initialCooltime, isKeepBattle, idx,
		idx, level, faceTarget,
		idx, level, faceTarget, cooltime,
		idx, initialCooltime,
		idx, level, facePos,
		idx, faceTarget, level, faceTargetTick,
		pfaceTarget, rob, idx,
		faceTarget, rob, idx,
		prob, cooltime, isKeepBattle, idx,
		sequnce, idx,
		facePos, cooltime, initialCooltime, idx,
		facePos, initialCooltime, idx,
		limit, idx,
node.name="teleport" attribute sets:
		pos,
		pos, facePos, faceTarget,
		pos, prob,
		pos, cooltime, isKeepBattle,
		pos, cooltime,
		pos, isKeepBattle,
		pos, cooltime, initialCooltime,
node.name="standby" attribute sets:
		limit, faceTarget, cooltime, isKeepBattle,
		limit, cooltime, faceTarget,
		limit, faceTarget,
		limit, animation, faceTarget, isKeepBattle,
		limit, faceTarget, animation,
		limit, faceTarget, isKeepBattle,
		limit, facePos, faceTarget,
		limit, facePos, animation, faceTarget,
		limit, facePos,
		limit, faceTarget, cooltime, initialCooltime,
		limit, faceTarget, cooltime, initialCooltime, isKeepBattle,
		limit,
		limit, initialCooltime,
		limit, faceTarget, initialCooltime,
		limit, faceTarget, prop,
		limit, faceTarget, prob,
		limit, facePos, isKeepBattle,
		limit, facePos, animation,
		limit, facePos, animation, isKeepBattle,
		limit, facePos, cooltime, isKeepBattle,
		limit, faceTarget, animation, cooltime,
		limit, faceTarget, animation, cooltime, initialCooltime, isKeepBattle,
		limit, faceTarget, animation, cooltime, isKeepBattle,
		limit, isKeepBattle,
		limit, facePos, faceTarget, isKeepBattle,
		limit, facePos, cooltime, initialCooltime, isKeepBattle,
		limit, animation,
		limit, animation, cooltime, initialCooltime,
		limit, zfaceTarget,
		limit, cooltime,
		limit, cooltime, isKeepBattle,
		limit, facePos, cooltime,
		limit, facePos, cooltime, animation, initialCooltime,
		limit, facePos, cooltime, animation,
		limit, cooltime, animation, faceTarget, initialCooltime,
		limit, cooltime, animation, isKeepBattle,
		limit, animation, isKeepBattle,
		limit, cooltime, initialCooltime, isKeepBattle,
		limit, cooltime, faceTarget, facePos, initialCooltime,
		limit, cooltime, faceTarget, facePos,
		limit, cooltime, initialCooltime,
node.name="setData" attribute sets:
		key, value,
		key, value, cooltime,
node.name="target" attribute sets:
		type, from, to,
		cooltime, from, type, to,
		type, center, isKeepBattle,
		type, center,
		type, cooltime, center,
		type, additionalId, additionalLevel, target,
		cooltime, type, additionalId, additionalLevel, target,
		from, type, prob, to,
		from, type, to, isKeepBattle,
		type, additionalId, additionalLevel, isKeepBattle, target,
		type, additionalId, additionalLevel, isKeepBattle, target, rob,
		type,
		type, from, cooltime, to, initialCooltime,
		type, rank,
		cooltime, from, type, to, isKeepBattle,
		cooltime, type, isKeepBattle,
		cooltime, type,
		type, additionalId, additionalLevel, noChangeWhenNoTarget, target,
		from, type, target, to,
node.name="say" attribute sets:
		message, durationTick, delayTick,
		durationTick, message, cooltime,
		message, durationTick,
		durationTick, message, isKeepBattle,
		message, durationTick, delayTick, isKeepBattle,
		message, durationTick, cooltime, initialCooltime,
		durationTick, message, cooltime, isKeepBattle,
		durationTick, message, cooltime, delayTick,
		durationTick, message, prob,
node.name="SetValue" attribute sets:
		key, value,
		key, value, isModify,
		isKeepBattle, value, key,
		cooltime, key, value,
		cooltime, key, value, isModify,
		isKeepBattle, value, key, isModify,
		cooltime, initialCooltime, key, value,
node.name="conditions" attribute sets:
		cooltime,
		cooltime, initialCooltime,
		isKeepBattle,
		initialCooltime,
node.name="jump" attribute sets:
		pos, speed, heightMultiplier,
		pos, speed, heightMultiplier, cooltime, isKeepBattle,
		pos, speed, type, heightMultiplier,
		pos, speed, heightMultiplier, isKeepBattle,
		pos, speed, cooltime, heightMultiplier,
node.name="select" attribute sets:
		prob,
		useNpcProb,
node.name="move" attribute sets:
		destination, limit, cooltime,
		destination, limit,
		destination, limit, isKeepBattle,
		destination, limit, cooltime, isKeepBattle,
		destination, initialCooltime, limit, faceTarget, cooltime,
		destination, animation, speed,
		destination, animation, limit,
		initialCooltime, destination, limit, cooltime,
		destination,
		destination, cooltime,
		destination, limit, prob,
		destination, animation,
		destination, limit, animation, isKeepBattle,
		destination, limit, animation, speed,
		initialCooltime, destination, cooltime,
		destination, animation, cooltime, speed,
		initialCooltime, destination, cooltime, animation, speed,
node.name="summon" attribute sets:
		npcId, npcCountMax, npcCount, summonRot, summonPosOffset,
		npcId, npcCount, npcCountMax, group, summonPos,
		npcId, npcCountMax, npcCount, group, summonRadius, summonPosOffset,
		npcId, npcCount, npcCountMax, group, summonRadius, summonPos,
		delayTick, npcId, npcCountMax, npcCount, summonPosOffset, master, summonRadius, group,
		delayTick, npcId, npcCountMax, npcCount, group, summonRadius, summonPosOffset,
		npcId, npcCount, npcCountMax, group, option, summonPosOffset,
		npcId, cooltime, npcCount, npcCountMax, group, summonRadius, summonPosOffset,
		npcId, npcCount, npcCountMax, group, summonPosOffset,
		npcId, npcCountMax, npcCount, group, summonPos, summonRot,
		npcId, npcCountMax, npcCount, group, summonPos, master,
		npcId, npcCountMax, npcCount, group, summonPos, master, summonRot,
		delayTick, npcId, npcCountMax, npcCount, group, summonPos,
		npcId, cooltime, npcCount, npcCountMax, group, summonPos,
		npcId, npcCount, npcCountMax, group, summonPos, summonRot, isKeepBattle,
		npcId, delayTick, npcCount, npcCountMax, group, summonPos, summonRot,
		npcId, npcCount, npcCountMax, group, option, master, summonPosOffset, summonRot,
		npcId, npcCount, npcCountMax, group, summonPosOffset, summonRot,
		npcId, npcCount, npcCountMax, group, master, summonPosOffset, summonRot,
		npcId, npcCountMax, npcCount, group, lifeTime, summonPos, summonRot,
		npcId, npcCountMax, npcCount, group, lifeTime, summonPos,
		npcId, npcCountMax, npcCount, group, lifeTime, summonRot, summonPosOffset,
		npcId, npcCountMax, npcCount, option, group, summonPos, summonRot,
		npcId, npcCountMax, npcCount, group, summonPos, summonRadius, lifeTime,
		npcId, npcCountMax, npcCount, summonPos, lifeTime,
		npcId, npcCountMax, npcCount, summonPosOffset,
		npcId, npcCountMax, npcCount, group, summonRadius, summonTargetOffset,
		npcId, npcCountMax, npcCount, master, group, summonTargetOffset, summonRadius,
		npcId, npcCount, npcCountMax, group, option, master, summonPos,
		npcId, npcCount, npcCountMax, group, master, summonPosOffset, summonRot, lifeTime,
		npcId, delayTick, npcCount, npcCountMax, group, summonPosOffset, summonRot,
		npcId, delayTick, npcCount, npcCountMax, group, lifeTime, summonPos, summonRot,
		npcId, cooltime, npcCount, npcCountMax, group, summonPos, summonRot,
		npcId, npcCount, npcCountMax, summonPos, master,
		npcId, npcCount, npcCountMax, group, summonPos, summonRadius, master, lifeTime,
		npcId, npcCount, npcCountMax, summonPosOffset, master,
		npcId, npcCount, npcCountMax, group, master, summonRot, lifeTime, summonPos,
		npcId, npcCount, npcCountMax, master, summonPosOffset, group, summonRadius,
		npcId, npcCount, npcCountMax, group, lifeTime, summonPosOffset,
		npcId, npcCount, npcCountMax, lifeTime, summonPosOffset,
		npcId, npcCount, npcCountMax, summonPos,
		npcId, npcCount, npcCountMax, summonPosOffset, master, lifeTime,
		cooltime, npcId, npcCountMax, npcCount, group, summonPosOffset,
node.name="TriggerSetUserValue" attribute sets:
		triggerID, key, value,
		value, isKeepBattle, triggerID, key,
		cooltime, triggerID, key, value,
		cooltime, value, isKeepBattle, triggerID, key,
node.name="ride" attribute sets:
		type, isRideOff,
		type, isRideOff, rideNpcIDs,
node.name="SetSlaveValue" attribute sets:
		key, value,
		value, isKeepBattle, key, isModify,
		cooltime, key, value,
		key, value, isModify,
		cooltime, isKeepBattle, value, key,
		isKeepBattle, value, key,
		key, isRandom, value,
node.name="SetMasterValue" attribute sets:
		key, value,
		key, value, isModify,
		value, isKeepBattle, key,
		isKeepBattle, value, key, isModify,
		cooltime, key, value,
node.name="runaway" attribute sets:
		till, limit,
		skillIdx, limit,
		till, cooltime,
		till, limit, cooltime,
		till, limit, animation,
		till,
		till, limit, cooltime, initialCooltime,
		facePos, till, limit,
node.name="MinimumHp" attribute sets:
		hpPercent,
node.name="buff" attribute sets:
		level, type, id,
		type, level, cooltime, id,
		level, type, id, isKeepBattle,
		type, cooltime, id, initialCooltime,
		type, id,
		cooltime, type, id,
		type, id, isKeepBattle,
		type, level, id, isTarget,
		type, id, prob,
		cooltime, type, id, isKeepBattle,
		cooltime, type, id, initialCooltime, isKeepBattle,
node.name="TargetEffect" attribute sets:
		effectName,
node.name="ShowVibrate" attribute sets:
		groupID,
node.name="sidePopup" attribute sets:
		type, duration, illust, script, voice,
		duration, type, illust, script,
		type, duration, illust, sound,
		duration, type, illust,
node.name="SetValueRangeTarget" attribute sets:
		key, value, height, radius,
		cooltime, key, height, value, isModify, radius,
		key, value, height, radius, isModify,
		cooltime, key, height, value, radius,
		isKeepBattle, value, height, key, radius,
		key, value, radius,
		key, value,
		key, value, isModify, radius,
node.name="announce" attribute sets:
		message, durationTick,
		durationTick, message, cooltime,
node.name="ModifyRoomTime" attribute sets:
		timeTick,
		timeTick, isShowEffect,
node.name="TriggerModifyUserValue" attribute sets:
		triggerID, key, value,
node.name="Buff" attribute sets:
		level, type, id,
node.name="RemoveSlaves" attribute sets:
		isKeepBattle,
node.name="CreateInteractObject" attribute sets:
		normal, interactID, lifeTime, kfmName, reactable,
node.name values with no attributes: RemoveMe,
node[trace] child 'node' types: trace, skill, standby, select, SetValue, say, target, buff, sidePopup, conditions, runaway,
node[skill] can have child 'aiPreset' nodes
node[skill] child 'node' types: conditions, skill, teleport, standby, jump, select, move, target, say, SetValue, SetSlaveValue, SetMasterValue, summon, trace, runaway, HideVibrateAll, ShowVibrate, RemoveMe, TriggerSetUserValue, buff, SetValueRangeTarget, sidePopup, announce, MinimumHp, setData, ModifyRoomTime, RemoveSlaves,
node[teleport] child 'node' types: standby, teleport, skill, conditions, SetValue, target, select, summon, buff, trace,
node[standby] can have child 'aiPreset' nodes
node[standby] child 'node' types: setData, target, say, SetValue, jump, select, move, summon, teleport, standby, RemoveMe, TriggerSetUserValue, ride, SetSlaveValue, skill, SetMasterValue, trace, TargetEffect, RemoveSlaves, buff, conditions, HideVibrateAll, ShowVibrate, sidePopup, SetValueRangeTarget, announce, TriggerModifyUserValue, MinimumHp, runaway,
node[setData] child 'node' types: TriggerSetUserValue, buff, SetSlaveValue,
node[target] can have child 'aiPreset' nodes
node[target] child 'node' types: trace, teleport, standby, skill, SetValue, say, target, conditions, select, announce, summon, TargetEffect, ShowVibrate, buff, runaway,
node[say] can have child 'aiPreset' nodes
node[say] child 'node' types: standby, teleport, skill, SetValue, buff, move, select, jump, SetSlaveValue, TargetEffect, conditions, target,
node[SetValue] can have child 'aiPreset' nodes
node[SetValue] child 'node' types: target, say, SetValue, SetSlaveValue, skill, teleport, standby, summon, select, jump, TriggerSetUserValue, TargetEffect, sidePopup, SetValueRangeTarget, buff, conditions, RemoveSlaves, SetMasterValue, move, ShowVibrate, announce, TriggerModifyUserValue,
node[conditions] child 'condition' types: distanceOver, combatTime, distanceLess, skillRange, true, extraData, SlaveCount, hpOver, state, additional, feature, hpLess, DistanceLess, slaveCount,
node[jump] child 'node' types: standby, skill, target, SetValueRangeTarget, SetValue, summon, announce, jump, buff, move,
node[select] can have child 'aiPreset' nodes
node[select] child 'node' types: trace, teleport, standby, skill, conditions, move, target, say, SetValue, SetSlaveValue, setData, runaway, summon, buff, SetValueRangeTarget, announce, select, jump, RemoveMe, TriggerSetUserValue, TargetEffect, SetMasterValue,
node[move] child 'node' types: select, target, say, SetValue, skill, standby, SetMasterValue, summon, buff, SetSlaveValue, setData, runaway, SetValueRangeTarget,
node[summon] child 'node' types: SetValueRangeTarget, SetValue, summon, skill, standby, SetSlaveValue, conditions, select, move,
node[RemoveMe] child 'node' types: standby,
node[TriggerSetUserValue] can have child 'aiPreset' nodes
node[TriggerSetUserValue] child 'node' types: target, say, SetValue, move, buff, conditions, TriggerSetUserValue, MinimumHp, skill, standby, teleport, sidePopup, announce, ModifyRoomTime,
node[SetSlaveValue] child 'node' types: skill, standby, TriggerSetUserValue, conditions, ride, SetValue, select, buff,
node[SetMasterValue] can have child 'aiPreset' nodes
node[SetMasterValue] child 'node' types: skill, standby, SetMasterValue, SetValue, SetValueRangeTarget, select, summon, buff, TriggerModifyUserValue,
node[runaway] child 'node' types: skill, standby, select, buff, runaway, conditions,
node[buff] child 'node' types: skill, teleport, standby, jump, select, buff, target, say, SetValue, RemoveMe, TriggerSetUserValue, summon, SetSlaveValue, ModifyRoomTime, SetValueRangeTarget,
node[TargetEffect] child 'node' types: select, target,
node[ShowVibrate] child 'node' types: target,
node[SetValueRangeTarget] child 'node' types: select, jump, TriggerSetUserValue, standby, skill, SetValueRangeTarget, SetSlaveValue, summon, target,
node[announce] can have child 'aiPreset' nodes
node[announce] child 'node' types: select, skill, SetValue,
node[ModifyRoomTime] child 'node' types: skill,
node[TriggerModifyUserValue] child 'node' types: SetMasterValue, SetValue, TriggerModifyUserValue,
node[RemoveSlaves] child 'node' types: standby, TriggerSetUserValue, SetValueRangeTarget, SetValue,

condition.name values with attributes: distanceOver, combatTime, distanceLess, skillRange, extraData, SlaveCount, hpOver, state, additional, feature, hpLess, DistanceLess, slaveCount,
condition.name="distanceOver" attribute sets:
		value,
condition.name="combatTime" attribute sets:
		battleTimeBegin, battleTimeEnd, battleTimeLoop,
		battleTimeBegin, battleTimeLoop,
condition.name="distanceLess" attribute sets:
		value,
condition.name="skillRange" attribute sets:
		skillIdx,
		skillIdx, skillLev,
		isKeepBattle, skillIdx,
condition.name="extraData" attribute sets:
		key, value,
		key, op, value,
		isKeepBattle, value, op, key,
		value, isKeepBattle, key,
condition.name="SlaveCount" attribute sets:
		count,
		count, useSummonGroup, summonGroup,
condition.name="hpOver" attribute sets:
		value,
condition.name="state" attribute sets:
		targetState,
condition.name="additional" attribute sets:
		id,
		id, level,
		id, overlapCount,
		isTarget, id,
condition.name="feature" attribute sets:
		feature,
condition.name="hpLess" attribute sets:
		value,
condition.name="DistanceLess" attribute sets:
		value,
condition.name="slaveCount" attribute sets:
		slaveCount, slaveCountOp,
condition.name values with no attributes: true,
condition[distanceOver] child 'node' types: trace, standby, select,
condition[combatTime] can have child 'aiPreset' nodes
condition[combatTime] child 'node' types: conditions, select, summon, skill, standby, target, SetValue, say, SetMasterValue,
condition[distanceLess] child 'node' types: select, runaway,
condition[skillRange] can have child 'aiPreset' nodes
condition[skillRange] child 'node' types: select, trace, standby, skill, RemoveMe, conditions, say, SetValue, target, buff, move, SetSlaveValue,
condition[true] can have child 'aiPreset' nodes
condition[true] child 'node' types: teleport, standby, skill, jump, select, SetSlaveValue, target, SetValue, conditions, move, trace, sidePopup, SetValueRangeTarget, RemoveMe, TriggerSetUserValue, TargetEffect, buff, SetMasterValue, runaway, summon,
condition[extraData] can have child 'aiPreset' nodes
condition[extraData] child 'node' types: conditions, jump, select, target, say, SetValue, SetMasterValue, skill, teleport, standby, move, TriggerSetUserValue, RemoveMe, sidePopup, SetValueRangeTarget, buff, announce, summon, TriggerModifyUserValue, trace, SetSlaveValue, RemoveSlaves, MinimumHp, Buff,
condition[SlaveCount] child 'node' types: target, SetValue, move, buff, teleport, standby, skill, select, TriggerSetUserValue, SetSlaveValue, MinimumHp, summon,
condition[hpOver] can have child 'aiPreset' nodes
condition[hpOver] child 'node' types: conditions, select, target, SetValue, skill, standby, buff,
condition[state] child 'node' types: select, standby, trace, skill, TriggerSetUserValue, target, move,
condition[additional] can have child 'aiPreset' nodes
condition[additional] child 'node' types: buff, SetValue, say, target, select, skill, conditions, SetSlaveValue, standby, sidePopup, TriggerSetUserValue, RemoveMe, CreateInteractObject,
condition[feature] child 'node' types: skill, sidePopup, summon,
condition[hpLess] can have child 'aiPreset' nodes
condition[hpLess] child 'node' types: standby, skill, Suicide, MinimumHp, TriggerSetUserValue,
condition[DistanceLess] child 'node' types: skill,
condition[slaveCount] can have child 'aiPreset' nodes
*/

void parseAIXml(Parser& parser)
{
	const XmlLite::XmlNode* envNode = parser.Document.GetFirstChild();
	bool unknownValueFound = false;

	XmlLite::XmlReader::StackMarker rootMarker = parser.Document.GetStackMarker();

	if (parser.Verbose)
	{
		std::cout << parser.SubPath.GetPath() << std::endl;
	}

	printPath(parser);

	for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(rootMarker))
	{
		printPath(parser);

		if (strncmp(childNode->Name.data(), "battle", childNode->Name.size()) == 0)
		{
			XmlLite::XmlReader::StackMarker nodeMarker = parser.Document.GetStackMarker();

			for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(nodeMarker))
			{
				printPath(parser);

				if (!parser.battleChildren.contains(std::string(childNode->Name)))
				{
					parser.battleChildren.insert(std::string(childNode->Name));
					std::cout << "npcAi.battle child: " << childNode->Name << std::endl;
					unknownValueFound = true;
				}

				std::string name;
				std::vector<std::string> attributes;
				for (const XmlLite::XmlAttribute* attribute = parser.Document.GetNextAttribute(); attribute; attribute = parser.Document.GetNextAttribute())
				{
					if (strncmp(attribute->Name.data(), "name", attribute->Name.size()) != 0)
					{
						attributes.push_back(std::string(attribute->Name));
					}
					else
					{
						name = attribute->Value;
						if (!parser.battle_nodeData.contains(name))
						{
							std::cout << "npcAi.battle.node.name=\"" << attribute->Value << "\"" << std::endl;
							unknownValueFound = true;
							parser.battle_nodeData[name];
						}
					}
				}
				if (attributes.size())
				{
					bool foundMatching = false;
					auto& attributeSets = parser.battle_nodeData[name].AttributeSets;

					for (const auto& set : attributeSets)
					{
						if (set.size() != attributes.size()) continue;

						foundMatching = true;

						for (const auto& attribute : attributes)
						{
							if (!set.contains(attribute))
							{
								foundMatching = false;
							
								break;
							}
						}

						if (foundMatching)
						{
							break;
						}
					}

					if (!foundMatching)
					{
						attributeSets.push_back({});

						for (const auto& attribute : attributes)
						{
							if (!attributeSets.back().contains(attribute))
							{
								attributeSets.back().insert(attribute);
							}
						}
					}
				}

				XmlLite::XmlReader::StackMarker childMarker = parser.Document.GetStackMarker();

				for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(childMarker))
				{
					AttributeData& data = parser.battle_nodeData[name];

					data.IsTopLevel = true;
					data.Name = "npcAi.battle.node[" + name + "]";

					parseChild(parser, childNode, data, "battle.node", unknownValueFound);
				}
			}
		}
		else if (strncmp(childNode->Name.data(), "reserved", childNode->Name.size()) == 0)
		{
			XmlLite::XmlReader::StackMarker nodeMarker = parser.Document.GetStackMarker();

			for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(nodeMarker))
			{
				printPath(parser);

				if (!parser.reservedChildren.contains(std::string(childNode->Name)))
				{
					parser.reservedChildren.insert(std::string(childNode->Name));
					std::cout << "npcAi.reserved child: " << childNode->Name << std::endl;
					unknownValueFound = true;
				}

				std::string name;
				std::vector<std::string> attributes;
				for (const XmlLite::XmlAttribute* attribute = parser.Document.GetNextAttribute(); attribute; attribute = parser.Document.GetNextAttribute())
				{
					if (strncmp(attribute->Name.data(), "name", attribute->Name.size()) != 0)
					{
						attributes.push_back(std::string(attribute->Name));
					}
					else
					{
						name = attribute->Value;
						if (!parser.reserved_conditionData.contains(name))
						{
							std::cout << "npcAi.reserved.condition.name=\"" << attribute->Value << "\"" << std::endl;
							unknownValueFound = true;
							parser.reserved_conditionData[name];
						}
					}
				}
				if (attributes.size())
				{
					bool foundMatching = false;
					auto& attributeSets = parser.reserved_conditionData[name].AttributeSets;

					for (const auto& set : attributeSets)
					{
						if (set.size() != attributes.size()) continue;

						foundMatching = true;

						for (const auto& attribute : attributes)
						{
							if (!set.contains(attribute))
							{
								foundMatching = false;

								break;
							}
						}

						if (foundMatching)
						{
							break;
						}
					}

					if (!foundMatching)
					{
						attributeSets.push_back({});

						for (const auto& attribute : attributes)
						{
							if (!attributeSets.back().contains(attribute))
							{
								attributeSets.back().insert(attribute);
							}
						}
					}
				}

				XmlLite::XmlReader::StackMarker childMarker = parser.Document.GetStackMarker();

				for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(childMarker))
				{
					AttributeData& data = parser.reserved_conditionData[name];

					data.IsTopLevel = true;
					data.Name = "npcAi.reserved.condition[" + name + "]";

					parseChild(parser, childNode, data, "reserved.condition", unknownValueFound);
				}
			}
		}
		else if (strncmp(childNode->Name.data(), "battleEnd", childNode->Name.size()) == 0)
		{
			XmlLite::XmlReader::StackMarker nodeMarker = parser.Document.GetStackMarker();

			for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(nodeMarker))
			{
				printPath(parser);

				if (!parser.battleEndChildren.contains(std::string(childNode->Name)))
				{
					parser.battleEndChildren.insert(std::string(childNode->Name));
					std::cout << "npcAi.battleEnd child: " << childNode->Name << std::endl;
					unknownValueFound = true;
				}

				std::string name;
				std::vector<std::string> attributes;
				for (const XmlLite::XmlAttribute* attribute = parser.Document.GetNextAttribute(); attribute; attribute = parser.Document.GetNextAttribute())
				{
					if (strncmp(attribute->Name.data(), "name", attribute->Name.size()) != 0)
					{
						attributes.push_back(std::string(attribute->Name));
					}
					else
					{
						name = attribute->Value;
						if (!parser.battleEnd_nodeData.contains(name))
						{
							std::cout << "npcAi.battleEnd.node.name=\"" << attribute->Value << "\"" << std::endl;
							unknownValueFound = true;
							parser.battleEnd_nodeData[name];
						}
					}
				}
				if (attributes.size())
				{
					bool foundMatching = false;
					auto& attributeSets = parser.battleEnd_nodeData[name].AttributeSets;

					for (const auto& set : attributeSets)
					{
						if (set.size() != attributes.size()) continue;

						foundMatching = true;

						for (const auto& attribute : attributes)
						{
							if (!set.contains(attribute))
							{
								foundMatching = false;

								break;
							}
						}

						if (foundMatching)
						{
							break;
						}
					}

					if (!foundMatching)
					{
						attributeSets.push_back({});

						for (const auto& attribute : attributes)
						{
							if (!attributeSets.back().contains(attribute))
							{
								attributeSets.back().insert(attribute);
							}
						}
					}
				}

				XmlLite::XmlReader::StackMarker childMarker = parser.Document.GetStackMarker();

				for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(childMarker))
				{
					AttributeData& data = parser.battleEnd_nodeData[name];

					data.IsTopLevel = true;
					data.Name = "npcAi.battleEnd.node[" + name + "]";

					parseChild(parser, childNode, data, "battleEnd.node", unknownValueFound);
				}
			}
		}
		else if (strncmp(childNode->Name.data(), "aiPresets", childNode->Name.size()) == 0)
		{
			XmlLite::XmlReader::StackMarker nodeMarker = parser.Document.GetStackMarker();

			for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(nodeMarker))
			{
				printPath(parser);

				if (!parser.aiPresetsChildren.contains(std::string(childNode->Name)))
				{
					parser.aiPresetsChildren.insert(std::string(childNode->Name));
					std::cout << "npcAi.aiPresets child: " << childNode->Name << std::endl;
					unknownValueFound = true;
				}

				std::string name;
				std::vector<std::string> attributes;
				for (const XmlLite::XmlAttribute* attribute = parser.Document.GetNextAttribute(); attribute; attribute = parser.Document.GetNextAttribute())
				{
					if (strncmp(attribute->Name.data(), "name", attribute->Name.size()) != 0)
					{
						attributes.push_back(std::string(attribute->Name));
					}
					else
					{
						name = attribute->Value;
						if (!parser.aiPresets_aiPresetNames.contains(name))
						{
							std::cout << "npcAi.aiPresets.aiPreset.name=\"" << attribute->Value << "\"" << std::endl;
							unknownValueFound = true;
							parser.aiPresets_aiPresetNames.insert(name);
						}
					}
				}
				if (attributes.size())
				{
					bool foundMatching = false;
					auto& attributeSets = parser.aiPresets_aiPresetData["misc..."].AttributeSets;

					for (const auto& set : attributeSets)
					{
						if (set.size() != attributes.size()) continue;

						foundMatching = true;

						for (const auto& attribute : attributes)
						{
							if (!set.contains(attribute))
							{
								foundMatching = false;

								break;
							}
						}

						if (foundMatching)
						{
							break;
						}
					}

					if (!foundMatching)
					{
						attributeSets.push_back({});

						for (const auto& attribute : attributes)
						{
							if (!attributeSets.back().contains(attribute))
							{
								attributeSets.back().insert(attribute);
							}
						}
					}
				}

				XmlLite::XmlReader::StackMarker childMarker = parser.Document.GetStackMarker();

				for (const XmlLite::XmlNode* childNode = parser.Document.GetFirstChild(); childNode; childNode = parser.Document.GetNextSibling(childMarker))
				{
					AttributeData& data = parser.aiPresets_aiPresetData["misc..."];

					data.IsTopLevel = true;
					data.Name = "npcAi.aiPresets.aiPreset[misc]";

					parseChild(parser, childNode, data, "aiPresets.aiPreset", unknownValueFound);
				}
			}
		}
		else
		{

		}
	}

	if (unknownValueFound)
	{
		std::cout << parser.SubPath.GetPath() << std::endl;

		//XmlLite::XmlReader document2;
		//
		//document2.OpenDocument(contents);
		//
		//const XmlLite::XmlNode* envNode = document2.GetFirstChild();
		//unknownValueFound = true;
	}
}

int main(int argc, char** argv)
{
	fs::path ms2Root;

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "--root") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2Root = argv[i];
		}
	}

	Archive::ArchiveReader reader(ms2Root / "Data", false);

	struct StackEntry
	{
		Archive::ArchiveReader::Path Path;
		size_t Index = 0;
	};

	Archive::ArchiveReader::Path aiPath = reader.GetPath("Server/AI");

	std::cout << aiPath.GetPath() << std::endl;

	std::vector<StackEntry> stack = { { aiPath } };

	std::string contents;

	Parser parser;

	//parser.Verbose = true;

	std::unordered_set<std::string> aiFiles;

	while (stack.size())
	{
		StackEntry& entry = stack.back();

		if (entry.Index < entry.Path.ChildDirectories())
		{
			++entry.Index;

			stack.push_back({ entry.Path.ChildDirectory(entry.Index - 1), 0 });

			//std::cout << stack.back().Path.GetPath() << std::endl;

			continue;
		}

		for (size_t i = 0; i < entry.Path.ChildFiles(); ++i)
		{
			parser.SubPath = entry.Path.ChildFile(i);

			if (parser.SubPath.GetPath().string() == "server/ai/pet/ai_defaultpettaming.xml")
			std::cout << "\t" << parser.SubPath.GetPath() << std::endl;

			std::string path = parser.SubPath.GetPath().string().substr(10);

			aiFiles.insert(path);

			parser.SubPath.Read(contents);
			parser.Document.OpenDocument(contents);

			parseAIXml(parser);
		}

		stack.pop_back();
	}

	std::cout << "npcAi.battle children: ";

	for (const std::string& name : parser.battleChildren)
	{
		std::cout << name << ", ";
	}

	std::cout << std::endl;

	std::cout << "npcAi.reserved children: ";

	for (const std::string& name : parser.reservedChildren)
	{
		std::cout << name << ", ";
	}

	std::cout << std::endl;

	std::cout << "npcAi.battleEnd children: ";

	for (const std::string& name : parser.battleEndChildren)
	{
		std::cout << name << ", ";
	}

	std::cout << std::endl;

	std::cout << "npcAi.aiPresets children: ";

	for (const std::string& name : parser.aiPresetsChildren)
	{
		std::cout << name << ", ";
	}

	std::cout << std::endl;

	const auto printAttribs = [&parser](const char* childName, const std::unordered_map<std::string, AttributeData>& attributeData)
	{
		std::cout << std::endl;

		bool found = false;

		for (const auto& entryIndex : attributeData)
		{
			const std::string& name = entryIndex.first;
			const AttributeData& data = entryIndex.second;

			if (data.AttributeSets.size() != 0)
			{
				found = true;

				break;
			}
		}

		if (found)
		{
			std::cout << childName << ".name values with attributes: ";

			for (const auto& entryIndex : attributeData)
			{
				const std::string& name = entryIndex.first;
				const AttributeData& data = entryIndex.second;

				if (data.AttributeSets.size() == 0)
					continue;

				std::cout << name << ", ";
			}

			std::cout << std::endl;
		}

		bool skipped = false;

		for (const auto& entryIndex : attributeData)
		{
			const std::string& name = entryIndex.first;
			const AttributeData& data = entryIndex.second;

			if (data.AttributeSets.size() == 0)
			{
				skipped = true;
				continue;
			}

			std::cout << childName << ".name=\"" << name << "\" attribute sets:" << std::endl;

			for (const auto& set : data.AttributeSets)
			{
				std::cout << "\t";

				for (const std::string& attribute : set)
				{
					std::cout << attribute << ", ";
				}

				std::cout << std::endl;
			}
		}

		if (skipped)
		{
			std::cout << childName << ".name values with no attributes: ";

			for (const auto& entryIndex : attributeData)
			{
				const std::string& name = entryIndex.first;
				const AttributeData& data = entryIndex.second;

				if (data.AttributeSets.size() != 0)
					continue;

				std::cout << name << ", ";
			}

			std::cout << std::endl;
		}

		for (const auto& entryIndex : attributeData)
		{
			const std::string& name = entryIndex.first;
			const AttributeData& data = entryIndex.second;

			if (data.CanHaveAiPreset)
			{
				std::cout << childName << "[" << name << "] can have child 'aiPreset' nodes" << std::endl;
			}

			if (data.ChildNodes.size())
			{
				std::cout << childName << "[" << name << "] child 'node' types: ";

				for (const std::string& type : data.ChildNodes)
				{
					std::cout << type << ", ";
				}

				std::cout << std::endl;
			}

			if (data.ChildConditions.size())
			{
				std::cout << childName << "[" << name << "] child 'condition' types: ";

				for (const std::string& type : data.ChildConditions)
				{
					std::cout << type << ", ";
				}

				std::cout << std::endl;
			}
		}
	};

	printAttribs("npcAi.battle.node", parser.battle_nodeData);
	printAttribs("npcAi.reserved.condition", parser.reserved_conditionData);
	printAttribs("npcAi.battleEnd.node", parser.battleEnd_nodeData);
	printAttribs("npcAi.aiPresets.aiPreset", parser.aiPresets_aiPresetData);

	printAttribs("node", parser.nodeTypes);
	printAttribs("condition", parser.conditionTypes);

	Archive::ArchiveReader::Path npcPath = reader.GetPath("Xml/npc");

	std::cout << npcPath.GetPath() << std::endl;

	std::vector<StackEntry> stack2 = { { npcPath } };

			std::unordered_set<std::string> referenced;
			std::unordered_set<std::string> seen;
	while (stack2.size())
	{
		StackEntry& entry = stack2.back();

		if (entry.Index < entry.Path.ChildDirectories())
		{
			++entry.Index;

			stack2.push_back({ entry.Path.ChildDirectory(entry.Index - 1), 0 });

			//std::cout << stack.back().Path.GetPath() << std::endl;

			continue;
		}

		for (size_t i = 0; i < entry.Path.ChildFiles(); ++i)
		{
			parser.SubPath = entry.Path.ChildFile(i);

			//if (parser.SubPath.GetPath().string() == "server/ai/pet/ai_defaultpettaming.xml")
			//	std::cout << "\t" << parser.SubPath.GetPath() << std::endl;

			parser.SubPath.Read(contents);
			parser.Document.OpenDocument(contents);

			const XmlLite::XmlNode* ms2Node = parser.Document.GetFirstChild();
			bool unknownValueFound = false;

			XmlLite::XmlReader::StackMarker rootMarker = parser.Document.GetStackMarker();


			for (const XmlLite::XmlNode* envNode = parser.Document.GetFirstChild(); envNode; envNode = parser.Document.GetNextSibling(rootMarker))
			{
				XmlLite::XmlReader::StackMarker envMarker = parser.Document.GetStackMarker();

				for (const XmlLite::XmlNode* npcNode = parser.Document.GetFirstChild(); npcNode; npcNode = parser.Document.GetNextSibling(envMarker))
				{
					if (strncmp(npcNode->Name.data(), "aiInfo", npcNode->Name.size()) == 0)
					{
						for (const XmlLite::XmlAttribute* attribute = parser.Document.GetNextAttribute(); attribute; attribute = parser.Document.GetNextAttribute())
						{
							if (strncmp(attribute->Name.data(), "path", attribute->Name.size()) == 0)
							{
								std::string path = std::string{ attribute->Value };

								for (char& character : path)
								{
									if (character >= 'A' && character <= 'Z')
									{
										character += 'a' - 'A';
									}
								}

								if (path.size() != 0)
								{
									if (!aiFiles.contains(path))
									{
										if (!seen.contains(path))
										//std::cout << "found referenced path that doesnt exist: " << path << std::endl;
										seen.insert(path);
									}
									else 
									{if (!referenced.contains(path))
										referenced.insert(path);
									}
								}
							}
						}
					}
				}
			}

		}

		stack2.pop_back();
	}
	std::cout << "missing files found:" << std::endl;

	for (const std::string& path : seen) std::cout << "\t" << path << std::endl;
			std::cout << "referenced files found:" << std::endl;

			for (const std::string& path : referenced) std::cout << "\t" << path << std::endl;

	return 0;
}