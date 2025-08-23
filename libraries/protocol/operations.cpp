/*
 * AcloudBank
 */

#include <graphene/protocol/operations.hpp>
#include <graphene/protocol/fee_schedule.hpp>

#include <fc/io/raw.hpp>
#include <fc/uint128.hpp>

namespace graphene { namespace protocol {

uint64_t base_operation::calculate_data_fee( uint64_t bytes, uint64_t price_per_kbyte )
{
   auto result = (fc::uint128_t(bytes) * price_per_kbyte) / 1024;
   FC_ASSERT( result <= GRAPHENE_MAX_SHARE_SUPPLY );
   return static_cast<uint64_t>(result);
}

fc::optional< fc::future<void> > base_operation::validate_parallel( uint32_t skip )const
{
   validate();
   return fc::optional< fc::future<void> >();
}

void balance_claim_operation::validate()const
{
   FC_ASSERT( fee == asset() );
   FC_ASSERT( balance_owner_key != public_key_type() );
}

/**
 * @brief Used to validate operations in a polymorphic manner
 */
struct operation_validator
{
   typedef void result_type;
   template<typename T>
   void operator()( const T& v )const { v.validate(); }
};

struct operation_get_required_auth
{
   using result_type = void;

   flat_set<account_id_type>& active;
   flat_set<account_id_type>& owner;
   vector<authority>&         other;
   bool                       ignore_custom_op_reqd_auths;


   operation_get_required_auth( flat_set<account_id_type>& a,
                                flat_set<account_id_type>& own,
                                vector<authority>& oth,
                                bool ignore_custom_operation_required_auths )
       : active( a ), owner( own ), other( oth ),
         ignore_custom_op_reqd_auths( ignore_custom_operation_required_auths )
   {}

   template<typename T>
   void operator()( const T& v ) const {
      active.insert( v.fee_payer() );
      v.get_required_active_authorities( active );
      v.get_required_owner_authorities( owner );
      v.get_required_authorities( other );
   }

   void operator()( const custom_operation& op ) const {
      active.insert( op.fee_payer() );
      if( !ignore_custom_op_reqd_auths ) {
         op.get_required_active_authorities( active );
         op.get_required_owner_authorities( owner );
         op.get_required_authorities( other );
      }
   }
};

void operation_validate( const operation& op )
{
   op.visit( operation_validator() );
}

void operation_get_required_authorities( const operation& op,
                                         flat_set<account_id_type>& active,
                                         flat_set<account_id_type>& owner,
                                         vector<authority>& other,
                                         bool ignore_custom_operation_required_auths )
{
   op.visit( operation_get_required_auth( active, owner, other, ignore_custom_operation_required_auths ) );
}

} } // namespace graphene::protocol

GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::generic_operation_result )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::generic_exchange_operation_result )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::extendable_operation_result_dtl )

GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::op_wrapper )
