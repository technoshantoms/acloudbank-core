/*
 * Acloudbank
 */
#include <graphene/protocol/fee_schedule.hpp>

namespace graphene { namespace protocol {

   fee_schedule fee_schedule::get_default_impl()
   {
      fee_schedule result;
      const auto count = fee_parameters::count();
      result.parameters.reserve(count);
      for( size_t i = 0; i < count; ++i )
      {
         fee_parameters x;
         x.set_which(i);
         result.parameters.insert(x);
      }
      return result;
   }

   const fee_schedule& fee_schedule::get_default()
   {
      static const auto result = get_default_impl();
      return result;
   }

   struct zero_fee_visitor
   {
      using result_type = void;

      template<typename ParamType>
      result_type operator()(  ParamType& op )const
      {
         memset( (char*)&op, 0, sizeof(op) );
      }
   };

   void fee_schedule::zero_all_fees()
   {
      *this = get_default();
      for( fee_parameters& i : parameters )
         i.visit( zero_fee_visitor() );
      this->scale = 0;
   }

} } // graphene::protocol
