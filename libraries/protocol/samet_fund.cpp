/*
 * Acloudbank
 */

#include <graphene/protocol/samet_fund.hpp>

#include <fc/io/raw.hpp>

namespace graphene { namespace protocol {

void samet_fund_create_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( balance > 0, "Balance should be positive" );
}

void samet_fund_delete_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
}

void samet_fund_update_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( delta_amount.valid() || new_fee_rate.valid(), "Should change something" );
   if( delta_amount.valid() )
      FC_ASSERT( delta_amount->amount != 0, "Delta amount should not be zero" );
}

void samet_fund_borrow_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( borrow_amount.amount > 0, "Amount to borrow should be positive" );
}

void samet_fund_repay_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( repay_amount.amount > 0, "Amount to repay should be positive" );
   FC_ASSERT( fund_fee.amount >= 0, "Fund fee should not be negative" );
   FC_ASSERT( repay_amount.asset_id == fund_fee.asset_id,
             "Asset type of repay amount and fund fee should be the same" );
}

} } // graphene::protocol

GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_create_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_delete_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_update_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_borrow_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_repay_operation::fee_params_t )

GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_create_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_delete_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_update_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_borrow_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::samet_fund_repay_operation )
