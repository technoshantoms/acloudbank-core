
#pragma once

#include <graphene/net/node.hpp>

#include <list>

namespace graphene { namespace net {

class simulated_network : public node
{
public:
   ~simulated_network() override;
   explicit simulated_network(const std::string& user_agent) : node(user_agent) {}
   void      listen_to_p2p_network() const override {}
   void      connect_to_p2p_network() const override {}
   void      connect_to_endpoint(const fc::ip::endpoint& ep) const override {}

   fc::ip::endpoint get_actual_listening_endpoint() const override { return fc::ip::endpoint(); }

   void      sync_from(const item_id& current_head_block,
                       const std::vector<uint32_t>& hard_fork_block_numbers) const override {}
   void      broadcast(const message& item_to_broadcast) const override;
   void      add_node_delegate(std::shared_ptr<node_delegate> node_delegate_to_add);

   uint32_t get_connection_count() const override { return 8; }
private:
   struct node_info;
   void message_sender(std::shared_ptr<node_info> destination_node) const;
   std::list<std::shared_ptr<node_info>> network_nodes;
};

using simulated_network_ptr = std::shared_ptr<simulated_network>;

} } // graphene::net
