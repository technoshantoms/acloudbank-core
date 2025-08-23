/*
 * Acloudbank
 */

#pragma once
#include <graphene/chain/evaluator.hpp>

#include <graphene/protocol/ticket.hpp>

namespace graphene { namespace chain {

   class ticket_object;

   class ticket_create_evaluator : public evaluator<ticket_create_evaluator>
   {
      public:
         typedef ticket_create_operation operation_type;

         void_result do_evaluate( const ticket_create_operation& op );
         object_id_type do_apply( const ticket_create_operation& op );
   };

   class ticket_update_evaluator : public evaluator<ticket_update_evaluator>
   {
      public:
         typedef ticket_update_operation operation_type;

         void_result do_evaluate( const ticket_update_operation& op );
         generic_operation_result do_apply( const ticket_update_operation& op );

         const ticket_object* _ticket = nullptr;
   };

} } // graphene::chain
