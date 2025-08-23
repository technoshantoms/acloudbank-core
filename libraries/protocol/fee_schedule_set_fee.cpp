/*
 * Acloudbank
 */
#include <graphene/protocol/fee_schedule.hpp>

namespace graphene { namespace protocol {

   struct set_fee_visitor
   {
      using result_type = void;

      asset _fee;

      explicit set_fee_visitor( const asset& f ):_fee(f){}

      template<typename OpType>
      void operator()( OpType& op )const
      {
         op.fee = _fee;
      }
   };

   asset fee_schedule::set_fee( operation& op, const price& core_exchange_rate )const
   {
      auto f = calculate_fee( op, core_exchange_rate );
      for( size_t i=0; i<MAX_FEE_STABILIZATION_ITERATION; ++i )
      {
         op.visit( set_fee_visitor( f ) );
         auto f2 = calculate_fee( op, core_exchange_rate );
         if( f >= f2 )
            break;
         f = f2;
         if( 0 == i )
         {
            // no need for warnings on later iterations
            wlog( "set_fee requires multiple iterations to stabilize with core_exchange_rate ${p} on operation ${op}",
               ("p", core_exchange_rate) ("op", op) );
         }
      }
      return f;
   }

} } // graphene::protocol
