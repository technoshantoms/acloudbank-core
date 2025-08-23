
#pragma once

#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {

class withdraw_permission_create_evaluator : public evaluator<withdraw_permission_create_evaluator>
{
public:
   using operation_type = withdraw_permission_create_operation;

   void_result do_evaluate( const operation_type& op ) const;
   object_id_type do_apply( const operation_type& op ) const;
};

class withdraw_permission_claim_evaluator : public evaluator<withdraw_permission_claim_evaluator>
{
public:
   using operation_type = withdraw_permission_claim_operation;

   void_result do_evaluate( const operation_type& op ) const;
   void_result do_apply( const operation_type& op ) const;
};

class withdraw_permission_update_evaluator : public evaluator<withdraw_permission_update_evaluator>
{
public:
   using operation_type = withdraw_permission_update_operation;

   void_result do_evaluate( const operation_type& op ) const;
   void_result do_apply( const operation_type& op ) const;
};

class withdraw_permission_delete_evaluator : public evaluator<withdraw_permission_delete_evaluator>
{
public:
   using operation_type = withdraw_permission_delete_operation;

   void_result do_evaluate( const operation_type& op ) const;
   void_result do_apply( const operation_type& op ) const;
};

} } // graphene::chain
