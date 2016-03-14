/*
 * Copyright 2016 Gustaf Räntilä
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBQIO_SERVER_SOCKET_HPP
#define LIBQIO_SERVER_SOCKET_HPP

#include <q-io/types.hpp>
#include <q-io/event.hpp>
#include <q-io/ip.hpp>
#include <q-io/socket.hpp>

namespace q { namespace io {

/**
 * A server_socket is a socket which allows incoming connections.
 */
class server_socket
: public event
, public std::enable_shared_from_this< server_socket >
{
public:
	~server_socket( );

	/**
	 * Channel used to get incoming connections.
	 */
	q::readable_ptr< socket_ptr > clients( );

protected:
	static server_socket_ptr construct( const native_socket& );

private:
	server_socket( const native_socket& );

	friend class dispatcher;

	template< typename T > friend class q::shared_constructor;

	void sub_attach( const dispatcher_ptr& dispatcher ) noexcept override;

	void on_event_read( ) noexcept override;

	void close_socket( );
	void close_channel( );

	struct pimpl;
	std::unique_ptr< pimpl > pimpl_;
};

} } // namespace io, namespace q

#endif // LIBQIO_SERVER_SOCKET_HPP
