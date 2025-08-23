/*
 * Acloudbank
 */

#pragma once
#include <graphene/chain/evaluator.hpp>

#include <graphene/protocol/credit_offer.hpp>

namespace graphene { namespace chain {

   class credit_offer_object;

   class credit_offer_create_evaluator : public evaluator<credit_offer_create_evaluator>
   {
      public:
         using operation_type = credit_offer_create_operation;

         void_result do_evaluate( const credit_offer_create_operation& op ) const;
         object_id_type do_apply( const credit_offer_create_operation& op ) const;
   };

   class credit_offer_delete_evaluator : public evaluator<credit_offer_delete_evaluator>
   {
      public:
         using operation_type = credit_offer_delete_operation;

         void_result do_evaluate( const credit_offer_delete_operation& op );
         asset do_apply( const credit_offer_delete_operation& op ) const;

         const credit_offer_object* _offer = nullptr;
   };

   class credit_offer_update_evaluator : public evaluator<credit_offer_update_evaluator>
   {
      public:
         using operation_type = credit_offer_update_operation;

         void_result do_evaluate( const credit_offer_update_operation& op );
         void_result do_apply( const credit_offer_update_operation& op ) const;

         const credit_offer_object* _offer = nullptr;
   };

   class credit_offer_accept_evaluator : public evaluator<credit_offer_accept_evaluator>
   {
      public:
         using operation_type = credit_offer_accept_operation;

         void_result do_evaluate( const credit_offer_accept_operation& op );
         extendable_operation_result do_apply( const credit_offer_accept_operation& op ) const;

         const credit_offer_object* _offer = nullptr;
         const credit_deal_summary_object* _deal_summary = nullptr;
   };

   class credit_deal_repay_evaluator : public evaluator<credit_deal_repay_evaluator>
   {
      public:
         using operation_type = credit_deal_repay_operation;

         void_result do_evaluate( const credit_deal_repay_operation& op );
         extendable_operation_result do_apply( const credit_deal_repay_operation& op ) const;

         const credit_deal_object* _deal = nullptr;
   };

   class credit_deal_update_evaluator : public evaluator<credit_deal_update_evaluator>
   {
      public:
         using operation_type = credit_deal_update_operation;

         void_result do_evaluate( const credit_deal_update_operation& op );
         void_result do_apply( const credit_deal_update_operation& op ) const;

         const credit_deal_object* _deal = nullptr;
   };

} } // graphene::chain
