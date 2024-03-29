/*
 * Copyright (C) 2012 - 2012 FrenchCORE <http://www.frcore.com/>
 * Copyright (C) 2008 - 2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"

enum DruidSpells {
	DRUID_INCREASED_MOONFIRE_DURATION = 38414, DRUID_NATURES_SPLENDOR = 57865
};

// 62606 - Savage Defense
class spell_dru_savage_defense: public SpellScriptLoader {
public:
	spell_dru_savage_defense() :
			SpellScriptLoader("spell_dru_savage_defense") {
	}

	class spell_dru_savage_defense_AuraScript: public AuraScript {
		PrepareAuraScript(spell_dru_savage_defense_AuraScript)
		;

		uint32 absorbPct;

		bool Load() {
			absorbPct = SpellMgr::CalculateSpellEffectAmount(GetSpellProto(),
					EFFECT_0, GetCaster());
			return true;
		}

		void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount,
				bool & /*canBeRecalculated*/) {
			// Set absorbtion amount to unlimited
			amount = -1;
		}

		void Absorb(AuraEffect * aurEff, DamageInfo & /*dmgInfo*/,
				uint32 & absorbAmount) {
			absorbAmount = uint32(
					CalculatePctN(
							GetTarget()->GetTotalAttackPowerValue(BASE_ATTACK),
							absorbPct));
			aurEff->SetAmount(0);
		}

		void Register() {
			DoEffectCalcAmount +=
					AuraEffectCalcAmountFn(spell_dru_savage_defense_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
			OnEffectAbsorb +=
					AuraEffectAbsorbFn(spell_dru_savage_defense_AuraScript::Absorb, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_dru_savage_defense_AuraScript();
	}
};

class spell_dru_t10_restoration_4p_bonus: public SpellScriptLoader {
public:
	spell_dru_t10_restoration_4p_bonus() :
			SpellScriptLoader("spell_dru_t10_restoration_4p_bonus") {
	}

	class spell_dru_t10_restoration_4p_bonus_SpellScript: public SpellScript {
		PrepareSpellScript(spell_dru_t10_restoration_4p_bonus_SpellScript)
		;

		void FilterTargets(std::list<Unit*>& unitList) {
			unitList.remove(GetTargetUnit());
			std::list<Unit*> tempTargets;
			std::list<Unit*>::iterator end = unitList.end(), itr =
					unitList.begin();
			for (; itr != end; ++itr)
				if (GetCaster()->IsInRaidWith(*itr))
					tempTargets.push_back(*itr);

			itr = tempTargets.begin();
			std::advance(itr, urand(0, tempTargets.size() - 1));
			unitList.clear();
			unitList.push_back(*itr);
		}

		void Register() {
			OnUnitTargetSelect +=
					SpellUnitTargetFn(spell_dru_t10_restoration_4p_bonus_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_AREA_ALLY_DST);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_dru_t10_restoration_4p_bonus_SpellScript();
	}
};

// 54846 Glyph of Starfire
class spell_dru_glyph_of_starfire: public SpellScriptLoader {
public:
	spell_dru_glyph_of_starfire() :
			SpellScriptLoader("spell_dru_glyph_of_starfire") {
	}

	class spell_dru_glyph_of_starfire_SpellScript: public SpellScript {
		PrepareSpellScript(spell_dru_glyph_of_starfire_SpellScript)
		;

		bool Validate(SpellEntry const * /*spellEntry*/) {
			if (!sSpellStore.LookupEntry(DRUID_INCREASED_MOONFIRE_DURATION))
				return false;

			if (!sSpellStore.LookupEntry(DRUID_NATURES_SPLENDOR))
				return false;
			return true;
		}

		void HandleScriptEffect(SpellEffIndex /*effIndex*/) {
			Unit* caster = GetCaster();
			if (Unit* unitTarget = GetHitUnit())
				if (AuraEffect const * aurEff = unitTarget->GetAuraEffect(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DRUID, 0x00000002, 0, 0, caster->GetGUID())) {
					Aura* aura = aurEff->GetBase();

					uint32 countMin = aura->GetMaxDuration();
					uint32 countMax = GetSpellMaxDuration(aura->GetSpellProto())
							+ 9000;

					if (caster->HasAura(DRUID_INCREASED_MOONFIRE_DURATION))
						countMax += 3000;

					if (caster->HasAura(DRUID_NATURES_SPLENDOR))
						countMax += 3000;

					if (countMin < countMax) {
						aura->SetDuration(uint32(aura->GetDuration() + 3000));
						aura->SetMaxDuration(countMin + 3000);
					}
				}
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_dru_glyph_of_starfire_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_dru_glyph_of_starfire_SpellScript();
	}
};

// 69366 - Moonkin Form passive
class spell_dru_moonkin_form_passive: public SpellScriptLoader {
public:
	spell_dru_moonkin_form_passive() :
			SpellScriptLoader("spell_dru_moonkin_form_passive") {
	}

	class spell_dru_moonkin_form_passive_AuraScript: public AuraScript {
		PrepareAuraScript(spell_dru_moonkin_form_passive_AuraScript)
		;

		uint32 absorbPct;

		bool Load() {
			absorbPct = SpellMgr::CalculateSpellEffectAmount(GetSpellProto(),
					EFFECT_0, GetCaster());
			return true;
		}

		void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount,
				bool & /*canBeRecalculated*/) {
			// Set absorbtion amount to unlimited
			amount = -1;
		}

		void Absorb(AuraEffect * /*aurEff*/, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			// reduces all damage taken while Stunned in Cat Form
			if (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS)
					& (UNIT_FLAG_STUNNED))
				absorbAmount = CalculatePctN(dmgInfo.GetDamage(), absorbPct);
		}

		void Register() {
			DoEffectCalcAmount +=
					AuraEffectCalcAmountFn(spell_dru_moonkin_form_passive_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
			OnEffectAbsorb +=
					AuraEffectAbsorbFn(spell_dru_moonkin_form_passive_AuraScript::Absorb, EFFECT_0);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_dru_moonkin_form_passive_AuraScript();
	}
};

// 33851 - Primal Tenacity
class spell_dru_primal_tenacity: public SpellScriptLoader {
public:
	spell_dru_primal_tenacity() :
			SpellScriptLoader("spell_dru_primal_tenacity") {
	}

	class spell_dru_primal_tenacity_AuraScript: public AuraScript {
		PrepareAuraScript(spell_dru_primal_tenacity_AuraScript)
		;

		uint32 absorbPct;

		bool Load() {
			absorbPct = SpellMgr::CalculateSpellEffectAmount(GetSpellProto(),
					EFFECT_1, GetCaster());
			return true;
		}

		void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount,
				bool & /*canBeRecalculated*/) {
			// Set absorbtion amount to unlimited
			amount = -1;
		}

		void Absorb(AuraEffect * /*aurEff*/, DamageInfo & dmgInfo,
				uint32 & absorbAmount) {
			// reduces all damage taken while Stunned in Cat Form
			if ((GetTarget()->GetShapeshiftForm() == FORM_CAT)
					&& (GetTarget()->GetUInt32Value(UNIT_FIELD_FLAGS)
							& (UNIT_FLAG_STUNNED)))
				absorbAmount = CalculatePctN(dmgInfo.GetDamage(), absorbPct);
		}

		void Register() {
			DoEffectCalcAmount +=
					AuraEffectCalcAmountFn(spell_dru_primal_tenacity_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
			OnEffectAbsorb +=
					AuraEffectAbsorbFn(spell_dru_primal_tenacity_AuraScript::Absorb, EFFECT_1);
		}
	};

	AuraScript *GetAuraScript() const {
		return new spell_dru_primal_tenacity_AuraScript();
	}
};

// 50334 Berserk
class spell_dru_berserk: public SpellScriptLoader {
public:
	spell_dru_berserk() :
			SpellScriptLoader("spell_dru_berserk") {
	}

	class spell_dru_berserk_AuraScript: public AuraScript {
		PrepareAuraScript(spell_dru_berserk_AuraScript)
		;

		void HandleEffectApply(AuraEffect const * /*aurEff*/,
				AuraEffectHandleModes /*mode*/) {
			if (Unit* target = GetTarget())
				if (target->GetTypeId() == TYPEID_PLAYER)
					target->ToPlayer()->RemoveSpellCategoryCooldown(971, true);
		}

		void Register() {
			OnEffectApply +=
					AuraEffectApplyFn(spell_dru_berserk_AuraScript::HandleEffectApply, EFFECT_2, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript* GetAuraScript() const {
		return new spell_dru_berserk_AuraScript();
	}
};

class spell_dru_starfall_aoe: public SpellScriptLoader {
public:
	spell_dru_starfall_aoe() :
			SpellScriptLoader("spell_dru_starfall_aoe") {
	}

	class spell_dru_starfall_aoe_SpellScript: public SpellScript {
		PrepareSpellScript(spell_dru_starfall_aoe_SpellScript)
		;

		void FilterTargets(std::list<Unit*>& unitList) {
			unitList.remove(GetTargetUnit());
		}

		void Register() {
			OnUnitTargetSelect +=
					SpellUnitTargetFn(spell_dru_starfall_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_AREA_ENEMY_DST);
		}
	};

	SpellScript *GetSpellScript() const {
		return new spell_dru_starfall_aoe_SpellScript();
	}
};

class spell_druid_rejuvenation: public SpellScriptLoader {
public:
	spell_druid_rejuvenation() :
			SpellScriptLoader("spell_druid_rejuvenation") {
	}

	class spell_druid_rejuvenation_SpellScript: public SpellScript {
		PrepareSpellScript(spell_druid_rejuvenation_SpellScript)

		bool Validate(SpellEntry const * /*spellEntry*/) {
			return true;
		}

		void HandleDummy(SpellEffIndex /*effIndex*/) {
			if (Unit * caster = GetCaster()) {
				if (caster->GetTypeId() != TYPEID_PLAYER)
					return;

				caster->ToPlayer()->KilledMonsterCredit(44175, 0);
			}
		}

		void Register() {
			OnEffect +=
					SpellEffectFn(spell_druid_rejuvenation_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
		}
	};

	SpellScript* GetSpellScript() const {
		return new spell_druid_rejuvenation_SpellScript();
	}
};

// 40121 - Swift Flight Form (Passive)
class spell_dru_swift_flight_passive : public SpellScriptLoader
{
    public:
        spell_dru_swift_flight_passive() : SpellScriptLoader("spell_dru_swift_flight_passive") { }

        class spell_dru_swift_flight_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_dru_swift_flight_passive_AuraScript);

            void CalculateAmount(AuraEffect const* /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                Unit* caster = GetCaster();
                if (!caster || !caster->ToPlayer())
                    return;

                if (caster->ToPlayer()->Has310Flyer(false))
                    amount = 310;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_dru_swift_flight_passive_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_dru_swift_flight_passive_AuraScript();
        }
};

void AddSC_druid_spell_scripts() {
	new spell_dru_savage_defense();
	new spell_dru_t10_restoration_4p_bonus();
	new spell_dru_glyph_of_starfire();
	new spell_dru_moonkin_form_passive();
	new spell_dru_primal_tenacity();
	new spell_dru_berserk();
	new spell_dru_starfall_aoe();
	new spell_druid_rejuvenation();
	new spell_dru_swift_flight_passive();
}
