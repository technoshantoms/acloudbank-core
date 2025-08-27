
#pragma once

#include <graphene/protocol/operations.hpp>

#include <graphene/chain/hardfork.hpp>

#include <fc/reflect/typelist.hpp>

#include <type_traits>
#include <functional>

namespace graphene { namespace chain {
using namespace protocol;
namespace TL { using namespace fc::typelist; }

/**
 * @brief The hardfork_visitor struct checks whether a given operation type has been hardforked in or not
 *
 * This visitor can be invoked in several different ways, including operation::visit, typelist::runtime::dispatch, or
 * direct invocation by calling the visit() method passing an operation variant, narrow operation type, operation tag,
 * or templating on the narrow operation type
 */
struct hardfork_visitor {
   using result_type = bool;
   using first_unforked_op = custom_authority_create_operation;
   using BSIP_40_ops = TL::list< custom_authority_create_operation,
                                           custom_authority_update_operation,
                                           custom_authority_delete_operation>;
   using TNT_ops = TL::list<tank_create_operation, tank_update_operation, tank_delete_operation,
                            tank_query_operation, tap_open_operation, tap_connect_operation,
                            account_fund_connection_operation, connection_fund_account_operation>;
   using hf1604_ops = TL::list< limit_order_update_operation>;
   using hf2103_ops = TL::list< ticket_create_operation,
                                          ticket_update_operation>;
   using liquidity_pool_ops = TL::list< liquidity_pool_create_operation,
                                                  liquidity_pool_delete_operation,
                                                  liquidity_pool_deposit_operation,
                                                  liquidity_pool_withdraw_operation,
                                                  liquidity_pool_exchange_operation >;
   using liquidity_pool_update_op = TL::list< liquidity_pool_update_operation >;
   using samet_fund_ops = TL::list< samet_fund_create_operation,
                                              samet_fund_delete_operation,
                                              samet_fund_update_operation,
                                              samet_fund_borrow_operation,
                                              samet_fund_repay_operation >;
   using credit_offer_ops = TL::list< credit_offer_create_operation,
                                                credit_offer_delete_operation,
                                                credit_offer_update_operation,
                                                credit_offer_accept_operation,
                                                credit_deal_repay_operation,
                                                credit_deal_expired_operation >;
   using credit_deal_update_op = TL::list< credit_deal_update_operation >;

   fc::time_point_sec now;

   /// @note using head block time for all operations
   explicit hardfork_visitor(const fc::time_point_sec& head_block_time) : now(head_block_time) {}

   /// The real visitor implementations. Future operation types get added in here.
   /// @{
   template<typename Op>
   std::enable_if_t<operation::tag<Op>::value < operation::tag<first_unforked_op>::value, bool>
   visit() { return true; }
   template<typename Op>
   std::enable_if_t<TL::contains<BSIP_40_ops, Op>(), bool>
   visit() { return HARDFORK_BSIP_40_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<hf1604_ops, Op>(), bool>
   visit() { return HARDFORK_CORE_1604_PASSED(now); }
   std::enable_if_t<TL::contains<TNT_ops, Op>(), bool>
   visit()  { return HARDFORK_BSIP_72_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<hf2103_ops, Op>(), bool>
   visit() { return HARDFORK_CORE_2103_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<liquidity_pool_ops, Op>(), bool>
   visit() { return HARDFORK_LIQUIDITY_POOL_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<samet_fund_ops, Op>(), bool>
   visit() { return HARDFORK_CORE_2351_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<credit_offer_ops, Op>(), bool>
   visit() { return HARDFORK_CORE_2362_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<credit_deal_update_op, Op>(), bool>
   visit() { return HARDFORK_CORE_2595_PASSED(now); }
   template<typename Op>
   std::enable_if_t<TL::contains<liquidity_pool_update_op, Op>(), bool>
   visit() { return HARDFORK_CORE_2604_PASSED(now); }
   /// @}

   /// typelist::runtime::dispatch adaptor
   template<class W, class Op=typename W::type>
   std::enable_if_t<TL::contains<operation::list, Op>(), bool>
   operator()(W) { return visit<Op>(); }
   /// static_variant::visit adaptor
   template<class Op>
   std::enable_if_t<TL::contains<operation::list, Op>(), bool>
   operator()(const Op&) { return visit<Op>(); }
   /// Tag adaptor
   bool visit(operation::tag_type tag) const {
      return TL::runtime::dispatch(operation::list(), (size_t)tag, *this);
   }
   /// operation adaptor
   bool visit(const operation& op) const {
      return visit(op.which());
   }
};

} } // namespace graphene::chain
