/*
 * Acloudbank
 */

#pragma once
#include <graphene/chain/evaluator.hpp>

#include <graphene/protocol/samet_fund.hpp>

namespace graphene { namespace chain {

   class samet_fund_object;

   class samet_fund_create_evaluator : public evaluator<samet_fund_create_evaluator>
   {
      public:
         using operation_type = samet_fund_create_operation;

         void_result do_evaluate( const samet_fund_create_operation& op ) const;
         object_id_type do_apply( const samet_fund_create_operation& op ) const;
   };

   class samet_fund_delete_evaluator : public evaluator<samet_fund_delete_evaluator>
   {
      public:
         using operation_type = samet_fund_delete_operation;

         void_result do_evaluate( const samet_fund_delete_operation& op );
         asset do_apply( const samet_fund_delete_operation& op ) const;

         const samet_fund_object* _fund = nullptr;
   };

   class samet_fund_update_evaluator : public evaluator<samet_fund_update_evaluator>
   {
      public:
         using operation_type = samet_fund_update_operation;

         void_result do_evaluate( const samet_fund_update_operation& op );
         void_result do_apply( const samet_fund_update_operation& op ) const;

         const samet_fund_object* _fund = nullptr;
   };

   class samet_fund_borrow_evaluator : public evaluator<samet_fund_borrow_evaluator>
   {
      public:
         using operation_type = samet_fund_borrow_operation;

         void_result do_evaluate( const samet_fund_borrow_operation& op );
         extendable_operation_result do_apply( const samet_fund_borrow_operation& op ) const;

         const samet_fund_object* _fund = nullptr;
   };

   class samet_fund_repay_evaluator : public evaluator<samet_fund_repay_evaluator>
   {
      public:
         using operation_type = samet_fund_repay_operation;

         void_result do_evaluate( const samet_fund_repay_operation& op );
         extendable_operation_result do_apply( const samet_fund_repay_operation& op ) const;

         const samet_fund_object* _fund = nullptr;
   };

} } // graphene::chain
