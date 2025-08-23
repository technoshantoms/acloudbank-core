/*
 * Acloudbank
 */

#include <graphene/protocol/liquidity_pool.hpp>

#include <fc/io/raw.hpp>

namespace graphene { namespace protocol {

void liquidity_pool_create_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( asset_a < asset_b, "ID of the first asset should be smaller than ID of the second asset" );
   FC_ASSERT( asset_a != share_asset && asset_b != share_asset,
              "Share asset can not be the same as one of the assets in the pool" );
   FC_ASSERT( taker_fee_percent <= GRAPHENE_100_PERCENT, "Taker fee percent should not exceed 100%" );
   FC_ASSERT( withdrawal_fee_percent <= GRAPHENE_100_PERCENT, "Withdrawal fee percent should not exceed 100%" );
}

void liquidity_pool_delete_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
}

void liquidity_pool_update_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( taker_fee_percent.valid() || withdrawal_fee_percent.valid(), "Should update something" );
   if( taker_fee_percent.valid() )
      FC_ASSERT( *taker_fee_percent <= GRAPHENE_100_PERCENT, "Taker fee percent should not exceed 100%" );
   if( withdrawal_fee_percent.valid() )
      FC_ASSERT( 0 == *withdrawal_fee_percent, "Withdrawal fee percent can only be updated to zero" );
}

void liquidity_pool_deposit_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( amount_a.amount > 0 && amount_b.amount > 0, "Both amounts of the assets should be positive" );
   FC_ASSERT( amount_a.asset_id < amount_b.asset_id,
              "ID of the first asset should be smaller than ID of the second asset" );
}

void liquidity_pool_withdraw_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( share_amount.amount > 0, "Amount of the share asset should be positive" );
}

void liquidity_pool_exchange_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0, "Fee should not be negative" );
   FC_ASSERT( amount_to_sell.amount > 0, "Amount to sell should be positive" );
   FC_ASSERT( min_to_receive.amount > 0, "Minimum amount to receive should be positive" );
   FC_ASSERT( amount_to_sell.asset_id != min_to_receive.asset_id,
             "ID of the two assets should not be the same" );
}

} } // graphene::protocol

GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_create_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_delete_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_update_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_deposit_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_withdraw_operation::fee_params_t )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_exchange_operation::fee_params_t )

GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_create_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_delete_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_update_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_deposit_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_withdraw_operation )
GRAPHENE_IMPLEMENT_EXTERNAL_SERIALIZATION( graphene::protocol::liquidity_pool_exchange_operation )
