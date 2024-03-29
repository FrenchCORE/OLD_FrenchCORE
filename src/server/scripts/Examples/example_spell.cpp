/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
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

/*
 * An example of a spell script file
 * to bind a script to spell you have to add entry for it in `spell_script_names`
 * where `spell_id` is id of the spell to bind
 * and `ScriptName` is the name of a script assigned on registration
 */

#include "ScriptPCH.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"

class spell_ex_5581 : public SpellScriptLoader
{
    public:
        spell_ex_5581() : SpellScriptLoader("spell_ex_5581") { }

        class spell_ex_5581SpellScript : public SpellScript
        {
            // initialize script, this macro does compile time check for type of the function - prevents possible issues
            // if you have assigned wrong type of function to a hook you'll receive type conversion error during build
            // this line is required, otherwise you'll get XXXHandlerFunction - identifier not found errors
            PrepareSpellScript(spell_ex_5581SpellScript)
            enum Spells
            {
                SPELL_TRIGGERED = 18282
            };

            std::string localVariable;
            char * localVariable2;

            // function called on server startup
            // checks if script has data required for it to work
            bool Validate(SpellEntry const * /*spellEntry*/)
            {
                // check if spellid 70522 exists in dbc, we will trigger it later
                if (!sSpellStore.LookupEntry(SPELL_TRIGGERED))
                    return false;
                return true;
            }

            // function called just after script is added to spell
            // we initialize local variables if needed
            bool Load()
            {
                localVariable = "we're using local variable";
                localVariable2 = new char;
                return true;
                // return false - script will be immediately removed from the spell
                // for example - we don't want this script to be executed on a creature
                // if (GetCaster()->GetTypeID() != TYPEID_PLAYER)
                //     return false;
            }

            // function called just before script delete
            // we free allocated memory
            void Unload()
            {
                delete localVariable2;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                // we're handling SPELL_EFFECT_DUMMY in effIndex 0 here
                sLog->outString("SPELL_EFFECT_DUMMY is executed on target!");
                // make caster cast a spell on a unit target of effect
                if (Unit * target = GetHitUnit())
                    GetCaster()->CastSpell(target, SPELL_TRIGGERED, true);
            }

            void HandleBeforeHit()
            {
                sLog->outString("Spell is about to hit target!");
            }

            void HandleOnHit()
            {
                sLog->outString("Spell just hit target!");
            }

            void HandleAfterHit()
            {
                sLog->outString("Spell just finished hitting target!");
            }

            // register functions used in spell script - names of these functions do not matter
            void Register()
            {
                // we're registering our function here
                // function HandleDummy will be called when unit is hit by spell, just before default effect 0 handler
                //OnEffect += SpellEffectFn(spell_ex_5581SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnEffect += SpellEffectFn(spell_ex_5581SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                // this will prompt an error on startup because effect 0 of spell 49375 is set to SPELL_EFFECT_DUMMY, not SPELL_EFFECT_APPLY_AURA
                //OnEffect += SpellEffectFn(spell_gen_49375SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
                // this will make HandleDummy function to be called on first != 0 effect of spell 49375
                //OnEffect += SpellEffectFn(spell_gen_49375SpellScript::HandleDummy, EFFECT_FIRST_FOUND, SPELL_EFFECT_ANY);
                // this will make HandleDummy function to be called on all != 0 effect of spell 49375
                //OnEffect += SpellEffectFn(spell_gen_49375SpellScript::HandleDummy, EFFECT_ALL, SPELL_EFFECT_ANY);
                // bind handler to BeforeHit event of the spell
                BeforeHit += SpellHitFn(spell_ex_5581SpellScript::HandleBeforeHit);
                // bind handler to OnHit event of the spell
                OnHit += SpellHitFn(spell_ex_5581SpellScript::HandleOnHit);
                // bind handler to AfterHit event of the spell
                AfterHit += SpellHitFn(spell_ex_5581SpellScript::HandleAfterHit);
            }
        };

        // function which creates SpellScript
        SpellScript *GetSpellScript() const
        {
            return new spell_ex_5581SpellScript();
        }
};

class spell_ex_66244 : public SpellScriptLoader
{
    public:
        spell_ex_66244() : SpellScriptLoader("spell_ex_66244") { }

        class spell_ex_66244AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ex_66244AuraScript)
            enum Spells
            {
                SPELL_TRIGGERED = 18282
            };
            // function called on server startup
            // checks if script has data required for it to work
            bool Validate(SpellEntry const * /*spellEntry*/)
            {
                // check if spellid exists in dbc, we will trigger it later
                if (!sSpellStore.LookupEntry(SPELL_TRIGGERED))
                    return false;
                return true;
            }

            // function called in aura constructor
            // we initialize local variables if needed
            bool Load()
            {
                // do not load script if aura is casted by player or caster not avalible
                if (Unit * caster = GetCaster())
                    if (caster->GetTypeId() == TYPEID_PLAYER)
                        return true;
                return false;
            }

            void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                sLog->outString("Aura Effect is about to be applied on target!");
                Unit * target = GetTarget();
                // cast spell on target on aura apply
                target->CastSpell(target, SPELL_TRIGGERED, true);
            }

            void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                sLog->outString("Aura Effect is just removed on target!");
                Unit * target = GetTarget();
                Unit * caster = GetCaster();
                // caster may be not avalible (logged out for example)
                if (!caster)
                    return;
                // cast spell on caster on aura remove
                target->CastSpell(caster, SPELL_TRIGGERED, true);
            }

            void HandleEffectPeriodic(AuraEffect const * /*aurEff*/)
            {
                sLog->outString("Perioidic Aura Effect is does a tick on target!");
                Unit * target = GetTarget();
                // aura targets damage self on tick
                target->DealDamage(target, 100);
            }

            void HandleEffectPeriodicUpdate(AuraEffect * aurEff)
            {
                sLog->outString("Perioidic Aura Effect is now updated!");
                // we're doubling aura amount every tick
                aurEff->ChangeAmount(aurEff->GetAmount() * 2);
            }

            void HandleEffectCalcAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & canBeRecalculated)
            {
                sLog->outString("Amount of Aura Effect is being calculated now!");
                // we're setting amount to 100
                amount = 100;
                // amount will be never recalculated due to applying passive aura
                canBeRecalculated = false;
            }

            void HandleEffectCalcPeriodic(AuraEffect const * /*aurEff*/, bool & isPeriodic, int32 & amplitude)
            {
                sLog->outString("Periodic data of Aura Effect is being calculated now!");
                // we're setting aura to be periodic and tick every 10 seconds
                isPeriodic = true;
                amplitude = 2 * IN_MILLISECONDS;
            }

            void HandleEffectCalcSpellMod(AuraEffect const * /*aurEff*/, SpellModifier *& spellMod)
            {
                sLog->outString("SpellMod data of Aura Effect is being calculated now!");
                // we don't want spellmod for example
                if (spellMod)
                {
                    delete spellMod;
                    spellMod = NULL;
                }
                /*
                // alternative: we want spellmod for spell which doesn't have it
                if (!spellMod)
                {
                    spellMod = new SpellModifier(GetAura());
                    spellMod->op = SPELLMOD_DOT;
                    spellMod->type = SPELLMOD_PCT;
                    spellMod->spellId = GetId();
                    spellMod->mask[1] = 0x00002000;
                }
                */
            }

            // function registering
            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_ex_66244AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_ex_66244AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_ex_66244AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
                OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_ex_66244AuraScript::HandleEffectPeriodicUpdate, EFFECT_0, SPELL_AURA_DUMMY);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_ex_66244AuraScript::HandleEffectCalcAmount, EFFECT_0, SPELL_AURA_DUMMY);
                DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_ex_66244AuraScript::HandleEffectCalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
                DoEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_ex_66244AuraScript::HandleEffectCalcSpellMod, EFFECT_0, SPELL_AURA_DUMMY);
                /*OnApply += AuraEffectApplyFn();
                OnRemove += AuraEffectRemoveFn();
                DoCheckAreaTarget += AuraCheckAreaTargetFn();*/
            }
            /*
            void OnApply()
            {
            }

            void OnRemove()
            {
            }

            bool DoCheckAreaTarget(Unit * proposedTarget)
            {
            }*/
        };

        // function which creates AuraScript
        AuraScript *GetAuraScript() const
        {
            return new spell_ex_66244AuraScript();
        }
};

// example usage of OnEffectAbsorb and AfterEffectAbsorb hooks
class spell_ex_absorb_aura : public SpellScriptLoader
{
    public:
        spell_ex_absorb_aura() : SpellScriptLoader("spell_ex_absorb_aura") { }

        class spell_ex_absorb_auraAuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ex_absorb_auraAuraScript)
            enum Spells
            {
                SPELL_TRIGGERED = 18282
            };

            void HandleOnEffectAbsorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                sLog->outString("Our aura is now absorbing damage done to us!");
                // absorb whole damage done to us
                absorbAmount = dmgInfo.GetDamage();
            }

            void HandleAfterEffectAbsorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
            {
                sLog->outString("Our aura has absorbed %u damage!", absorbAmount);
            }

            // function registering
            void Register()
            {
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_ex_absorb_auraAuraScript::HandleOnEffectAbsorb, EFFECT_0);
                AfterEffectAbsorb += AuraEffectAbsorbFn(spell_ex_absorb_auraAuraScript::HandleAfterEffectAbsorb, EFFECT_0);
            }
        };

        // function which creates AuraScript
        AuraScript *GetAuraScript() const
        {
            return new spell_ex_absorb_auraAuraScript();
        }
};

// example usage of OnEffectManaShield and AfterEffectManaShield hooks
// see spell_ex_absorb_aura, these hooks work the same as OnEffectAbsorb and AfterEffectAbsorb

// this function has to be added to function set in ScriptLoader.cpp
void AddSC_example_spell_scripts()
{
    new spell_ex_5581;
    new spell_ex_66244;
    new spell_ex_absorb_aura;
}

/* empty script for copypasting
class spell_ex : public SpellScriptLoader
{
    public:
        spell_ex() : SpellScriptLoader("spell_ex") { }

        class spell_ex_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ex_SpellScript)
            //bool Validate(SpellEntry const * spellEntry){return true;}
            //bool Load(){return true;}
            //void Unload(){}

            //void Function(SpellEffIndex effIndex) //OnEffect += SpellEffectFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_EFFECT_ANY);
            //void Function() //OnHit += SpellEffectFn(spell_ex_SpellScript::Function);
            void Register()
            {
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_ex_SpellScript();
        }
};
*/

/* empty script for copypasting
class spell_ex : public SpellScriptLoader
{
    public:
        spell_ex() : SpellScriptLoader("spell_ex") { }

        class spell_ex_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ex)
            //bool Validate(SpellEntry const * spellEntry){return true;}
            //bool Load(){return true;}
            //void Unload(){}

            //void spell_ex_SpellScript::Function(AuraEffect const * aurEff, AuraEffectHandleModes mode) //OnEffectApply += AuraEffectApplyFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
            //void spell_ex_SpellScript::Function(AuraEffect const * aurEff, AuraEffectHandleModes mode) //OnEffectRemove += AuraEffectRemoveFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY, AURA_EFFECT_HANDLE_REAL);
            //void spell_ex_SpellScript::Function(AuraEffect const * aurEff) //OnEffectPeriodic += AuraEffectPeriodicFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY);
            //void spell_ex_SpellScript::Function(AuraEffect * aurEff) //OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY);
            //void spell_ex_SpellScript::Function(AuraEffect const * aurEff, int32 & amount, bool & canBeRecalculated) //DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY);
            //void spell_ex_SpellScript::Function(AuraEffect const * aurEff, bool & isPeriodic, int32 & amplitude) //OnEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY);
            //void spell_ex_SpellScript::Function(AuraEffect const * aurEff, SpellModifier *& spellMod) //OnEffectCalcSpellMod += AuraEffectCalcSpellModFn(spell_ex_SpellScript::Function, EFFECT_ANY, SPELL_AURA_ANY);
            void Register()
            {
            }
        };

        AuraScript *GetAuraScript() const
        {
            return new spell_ex_AuraScript();
        }
};
*/