/*
 * Acloudbank
 */

#pragma once
#include <graphene/chain/evaluator.hpp>

#include <graphene/protocol/liquidity_pool.hpp>

namespace graphene { namespace chain {

   class asset_object;
   class asset_dynamic_data_object;
   class liquidity_pool_object;

   class liquidity_pool_create_evaluator : public evaluator<liquidity_pool_create_evaluator>
   {
      public:
         using operation_type = liquidity_pool_create_operation;

         void_result do_evaluate( const liquidity_pool_create_operation& op );
         generic_operation_result do_apply( const liquidity_pool_create_operation& op );

      private:
         const asset_object* _share_asset = nullptr;
   };

   class liquidity_pool_delete_evaluator : public evaluator<liquidity_pool_delete_evaluator>
   {
      public:
         using operation_type = liquidity_pool_delete_operation;

         void_result do_evaluate( const liquidity_pool_delete_operation& op );
         generic_operation_result do_apply( const liquidity_pool_delete_operation& op ) const;

      private:
         const liquidity_pool_object* _pool = nullptr;
         const asset_object* _share_asset = nullptr;
   };

   class liquidity_pool_update_evaluator : public evaluator<liquidity_pool_update_evaluator>
   {
      public:
         using operation_type = liquidity_pool_update_operation;

         void_result do_evaluate( const liquidity_pool_update_operation& op );
         void_result do_apply( const liquidity_pool_update_operation& op ) const;

      private:
         const liquidity_pool_object* _pool = nullptr;
   };

   class liquidity_pool_deposit_evaluator : public evaluator<liquidity_pool_deposit_evaluator>
   {
      public:
         using operation_type = liquidity_pool_deposit_operation;

         void_result do_evaluate( const liquidity_pool_deposit_operation& op );
         generic_exchange_operation_result do_apply( const liquidity_pool_deposit_operation& op );

      private:
         const liquidity_pool_object* _pool = nullptr;
         const asset_dynamic_data_object* _share_asset_dyn_data = nullptr;
         asset _account_receives;
         asset _pool_receives_a;
         asset _pool_receives_b;
   };

   class liquidity_pool_withdraw_evaluator : public evaluator<liquidity_pool_withdraw_evaluator>
   {
      public:
         using operation_type = liquidity_pool_withdraw_operation;

         void_result do_evaluate( const liquidity_pool_withdraw_operation& op );
         generic_exchange_operation_result do_apply( const liquidity_pool_withdraw_operation& op );

      private:
         const liquidity_pool_object* _pool = nullptr;
         const asset_dynamic_data_object* _share_asset_dyn_data = nullptr;
         asset _pool_pays_a;
         asset _pool_pays_b;
         asset _fee_a;
         asset _fee_b;
   };

   class liquidity_pool_exchange_evaluator : public evaluator<liquidity_pool_exchange_evaluator>
   {
      public:
         using operation_type = liquidity_pool_exchange_operation;

         void_result do_evaluate( const liquidity_pool_exchange_operation& op );
         generic_exchange_operation_result do_apply( const liquidity_pool_exchange_operation& op );

      private:
         const liquidity_pool_object* _pool = nullptr;
         const asset_object* _pool_pays_asset = nullptr;
         const asset_object* _pool_receives_asset = nullptr;
         asset _pool_pays;
         asset _pool_receives;
         asset _account_receives;
         asset _maker_market_fee;
         asset _taker_market_fee;
         asset _pool_taker_fee;
   };

} } // graphene::chain
