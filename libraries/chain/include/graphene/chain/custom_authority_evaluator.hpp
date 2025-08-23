/*
 * Acloudbank
 */

#pragma once

#include <graphene/protocol/restriction_predicate.hpp>

#include <graphene/chain/evaluator.hpp>

namespace graphene { namespace chain {
class custom_authority_object;

class custom_authority_create_evaluator : public evaluator<custom_authority_create_evaluator> {
public:
   using operation_type = custom_authority_create_operation;

   void_result do_evaluate(const operation_type& op);
   object_id_type do_apply(const operation_type& op);
};

class custom_authority_update_evaluator : public evaluator<custom_authority_update_evaluator> {
public:
   using operation_type = custom_authority_update_operation;
   const custom_authority_object* old_object = nullptr;

   void_result do_evaluate(const operation_type& op);
   void_result do_apply(const operation_type& op);
};

class custom_authority_delete_evaluator : public evaluator<custom_authority_delete_evaluator> {
public:
   using operation_type = custom_authority_delete_operation;
   const custom_authority_object* old_object = nullptr;

   void_result do_evaluate(const operation_type& op);
   void_result do_apply(const operation_type& op);
};

} } // graphene::chain
