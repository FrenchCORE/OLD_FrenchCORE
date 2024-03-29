/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 * 
 * Copyright (C) 2012 - 2012 FrenchCORE <http://www.frcore.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef FRENCHCORE_DBCSFRM_H
#define FRENCHCORE_DBCSFRM_H

const char Achievementfmt[]="niixsxiixixxii";
//const std::string CustomAchievementfmt="pppaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaapapaaaaaaaaaaaaaaaaaapp";
//const std::string CustomAchievementIndex = "ID";
const char AchievementCriteriafmt[]="niiiiiiiisiiiiixxxxxxxx";
const char AreaTableEntryfmt[]="iiinixxxxxisixxxxxxxxxxxx";
const char AreaGroupEntryfmt[]="niiiiiii";
const char AreaPOIEntryfmt[]="niiiiiiiiiiiffixixxixx";
const char AreaTriggerEntryfmt[]="nifffxxxfffff";
const char ArmorLocationfmt[]="nfffff";
const char AuctionHouseEntryfmt[]="niiix";
const char BankBagSlotPricesEntryfmt[]="ni";
const char BarberShopStyleEntryfmt[]="nixxxiii";
const char BattlemasterListEntryfmt[]="niiiiiiiiixsiiiiiiix";
const char CharStartOutfitEntryfmt[]="diiiiiiiiiiiiiiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char CharTitlesEntryfmt[]="nxsxix";
const char ChatChannelsEntryfmt[]="nixsx";
                                                            // ChatChannelsEntryfmt, index not used (more compact store)
const char ChrClassesEntryfmt[]="nixsxxxixiixxx";
const char ChrRacesEntryfmt[]="nxixiixixxxxixsxxxxxixxx";
const char CinematicSequencesEntryfmt[]="nxxxxxxxxx";
const char CreatureDisplayInfofmt[]="nxxxfxxxxxxxxxxxx";
const char CreatureFamilyfmt[]="nfifiiiiixsx";
const char CreatureSpellDatafmt[]="niiiixxxx";
const char CreatureTypefmt[]="nxx";
const char CurrencyTypesfmt[]="nxxxxxxiixx";
const char DestructibleModelDatafmt[]="nxxixxxixxxixxxixxx";
const char DungeonEncounterfmt[]="niixisxx";
const char DurabilityCostsfmt[]="niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[]="nf";
const char EmotesEntryfmt[]="nxxiiix";
const char EmotesTextEntryfmt[]="nxixxxxxxxxxxxxxxxx";
const char FactionEntryfmt[]="niiiiiiiiiiiiiiiiiiffixsxx";
const char FactionTemplateEntryfmt[]="niiiiiiiiiiiii";
const char GameObjectDisplayInfofmt[]="nxxxxxxxxxxxffffffxxx";
const char GemPropertiesEntryfmt[]="nixxix";
const char GlyphPropertiesfmt[]="niii";
const char GlyphSlotfmt[]="nii";
const char GtBarberShopCostBasefmt[]="xf";
const char GtCombatRatingsfmt[]="xf";
const char GtChanceToMeleeCritBasefmt[]="xf";
const char GtChanceToMeleeCritfmt[]="xf";
const char GtChanceToSpellCritBasefmt[]="xf";
const char GtChanceToSpellCritfmt[]="xf";
const char GtOCTClassCombatRatingScalarfmt[]="df";
const char GtOCTRegenHPfmt[]="xf";
//const char GtOCTRegenMPfmt[]="f";
const char GtRegenHPPerSptfmt[]="xf";
const char GtRegenMPPerSptfmt[]="xf";
const char GtSpellScalingfmt[]="nf";
const char Holidaysfmt[]="nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char ItemArmorQualityfmt[]="nfffffffi";
const char ItemArmorShieldfmt[]="nifffffff";
const char ItemArmorTotalfmt[]="niffff";
const char ItemBagFamilyfmt[]="nx";
//const char ItemDisplayTemplateEntryfmt[]="nxxxxxxxxxxixxxxxxxxxxx";
//const char ItemCondExtCostsEntryfmt[]="xiii";
const char ItemDamagefmt[]="nfffffffi";
const char ItemExtendedCostEntryfmt[]="nxxiiiiiiiiiiiixiiiiiiiiiixxxxx";
const char ItemLimitCategoryEntryfmt[]="nxii";
const char ItemRandomPropertiesfmt[]="nxiiiiis";
const char ItemRandomSuffixfmt[]="nsxiiiiiiiiii";
const char ItemReforgefmt[]="nifif";
const char ItemSetEntryfmt[]="dsiiiiiiiiiixxxxxxxiiiiiiiiiiiiiiiiii"; /// "dsxxxxxxxxxxxxxxxxxiiiiiiiiiiiiiiiiii"
const char LFGDungeonEntryfmt[]="nxiiiiiiixixxixix";
const char LockEntryfmt[]="niiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
const char MailTemplateEntryfmt[]="nxs";
const char MapEntryfmt[]="nxixxxsixxixiffxiixx";
const char MapDifficultyEntryfmt[]="diisiix";
const char MovieEntryfmt[]="nxxx";
const char MountCapabilityfmt[]="niixxiii";
const char MountTypefmt[]="niiiiiiiiiiiiiiiiixxxxxxx";
const char OverrideSpellDatafmt[]="niiiiiiiiiixx";
const char QuestFactionRewardfmt[]="niiiiiiiiii";
const char QuestSortEntryfmt[]="nx";
const char QuestXPfmt[]="niiiiiiiiii";
const char PvPDifficultyfmt[]="diiiii";
const char RandomPropertiesPointsfmt[]="niiiiiiiiiiiiiii";
const char ScalingStatDistributionfmt[]="niiiiiiiiiiiiiiiiiiiixi";
const char ScalingStatValuesfmt[]="iniiiiiiiiiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxx";
const char SkillLinefmt[]="nixsxixi";
const char SkillLineAbilityfmt[]="niiiixxiiiiixx";
const char SoundEntriesfmt[]="nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellCastTimefmt[]="nixx";
const std::string CustomSpellCastTimeEntryfmt="ppaa";
const std::string CustomSpellCastTimeEntryIndex="id";
const char SpellDifficultyfmt[]="niiii";
const std::string CustomSpellDifficultyfmt="ppppp";
const std::string CustomSpellDifficultyIndex="id";
const char SpellDurationfmt[]="niii";
const std::string CustomDurationEntryfmt="pppp";
const std::string CustomDurationEntryIndex="id";
//const std::string CustomSpellEntryfmt="pppppppppaappapaaaaaaaaapaaaaaaaaaaaaaaaaaaaaaappppaaaaaaaaapaappppappppaaappppppppppppppppppaaapppaaapppppppppaaappppppppppppppppppppppppaaaaaappppaapppaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaappppapaaaa";
const char True_SpellEntryfmt[]=      "iiiiiiiiiixiiiifiiiisixxiixxixiiiiiiixiiiiixiixiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiifffiiiiiiiiiiiiiiiiiifffiiifffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffffffiiiiiiiiiii";
const std::string CustomSpellEntryIndex = "Id";
const char SpellEntryfmt[]=           "niiiiiiiiixiiiifiiiisixxiixxixiiiiiiixiiiiixiix";
const std::string CustomSpellEntryfmt="ppppppppppapppppppppaaaappaapapppppppappppppppa";
const char SpellAuraOptionsfmt[]="niiii";
const std::string CustomSpellAuraOptionsEntryfmt="ppppp";
const std::string CustomSpellAuraOptionsEntryIndex="id";
const char SpellAuraRestrictionsfmt[]="niiiiiiii";
const std::string CustomSpellAuraRestrictionsEntryfmt="ppppppppp";
const std::string CustomSpellAuraRestrictionsEntryIndex="id";
const char SpellCastingRequirementsfmt[]="nixxixi";
const std::string CustomSpellCastingRequirementsEntryfmt="ppaapap";
const std::string CustomSpellCastingRequirementsEntryIndex="id";
const char SpellCategoriesfmt[]="niiiiii";
const std::string CustomSpellCategoriesEntryfmt="ppppppp";
const std::string CustomSpellCategoriesEntryIndex="id";
const char SpellClassOptionsfmt[]="nxiiiix";
const std::string CustomSpellClassOptionsEntryfmt="pappppa";
const std::string CustomSpellClassOptionsEntryIndex="id";
const char SpellCooldownsfmt[]="niii";
const std::string CustomSpellCooldownsEntryfmt="pppp";
const std::string CustomSpellCooldownsEntryIndex="id";
const char SpellEffectfmt[]="nifiiiffiiiiiifixfiiiiiiii";
const std::string CustomSpellEffectEntryfmt="ppppppapppppppppappppppppp";
const std::string CustomSpellEffectEntryIndex="id";
const char SpellEquippedItemsfmt[]="niii";
const std::string CustomSpellEquippedItemsEntryfmt="pppp";
const std::string CustomSpellEquippedItemsEntryIndex="id";
const char SpellInterruptsfmt[]="nixixi";
const std::string CustomSpellInterruptsEntryfmt="ppapap";
const std::string CustomSpellInterruptsEntryIndex="id";
const char SpellLevelsfmt[]="niii";
const std::string CustomSpellLevelsEntryfmt="pppp";
const std::string CustomSpellLevelsEntryIndex="id";
const char SpellPowerfmt[]="niiiixx";
const std::string CustomSpellPowerEntryfmt="pppppaa";
const std::string CustomSpellPowerEntryIndex="id";
const char SpellReagentsfmt[]="niiiiiiiiiiiiiiii";
const std::string CustomSpellReagentsEntryfmt="ppppppppppppppppp";
const std::string CustomSpellReagentsEntryIndex="id";
const char SpellScalingfmt[]="niiiiffffffffffi";
const std::string CustomSpellScalingEntryfmt="nppppppppppppppp";
const std::string CustomSpellScalingEntryIndex="id";
const char SpellShapeshiftfmt[]="nixixx";
const std::string CustomSpellShapeshiftEntryfmt="ppapaa";
const std::string CustomSpellShapeshiftEntryIndex="id";
const char SpellTargetRestrictionsfmt[]="niiii";
const std::string CustomSpellTargetRestrictionsEntryfmt="ppppp";
const std::string CustomSpellTargetRestrictionsEntryIndex="id";
const char SpellTotemsfmt[]="niiii";
const std::string CustomSpellTotemsEntryfmt="ppppp";
const std::string CustomSpellTotemsEntryIndex="id";
const char SpellFocusObjectfmt[]="nx";
const char SpellItemEnchantmentfmt[]="nxiiiiiixxxiiisiiiiiiix";
const char SpellItemEnchantmentConditionfmt[]="nbbbbbxxxxxbbbbbbbbbbiiiiiXXXXX";
const char SpellRadiusfmt[]="nfxf";
const char SpellRangefmt[]="nffffixx";
const char SpellRuneCostfmt[]="niiii";
const char SpellShapeshiftFormfmt[]="nxxiixiiixxiiiiiiiixx";
const char SummonPropertiesfmt[] = "niiiii";
const char GuildPerksfmt[] = "nii";
const char TalentEntryfmt[]="niiiiiiiiixxixxxxxx";
const char TalentTabEntryfmt[]="nxxiiixxxii";
const char TalentTreePrimarySpellsfmt[]="niii";
const char TaxiNodesEntryfmt[]="nifffsii";
const char TaxiPathEntryfmt[]="niii";
const char TaxiPathNodeEntryfmt[]="diiifffiiii";
const char TotemCategoryEntryfmt[]="nxii";
const char VehicleEntryfmt[]="niffffiiiiiiiifffffffffffffffssssfifiixx";
const char VehicleSeatEntryfmt[]="niiffffffffffiiiiiifffffffiiifffiiiiiiiffiiiiixxxxxxxxxxxxxxxxxxxx";
const char WMOAreaTableEntryfmt[]="niiixxxxxiixxxx";
const char WorldMapAreaEntryfmt[]="xinxffffixxx";
const char WorldMapOverlayEntryfmt[]="nxiiiixxxxxxxxx";
const char WorldSafeLocsEntryfmt[]="nifffx";
const char PhaseEntryfmt[]="nsi";  //testing
#endif