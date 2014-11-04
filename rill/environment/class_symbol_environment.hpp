//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <utility>

#include "../config/macros.hpp"

#include "environment_base.hpp"


namespace rill
{
    enum class class_builtin_kind
    {
        k_none,
        k_void,
        k_int8,
        k_int16,
        k_int32,
        k_type,
        k_bool,
        k_string,
        k_array,
        k_ptr,
    };

    //
    // class
    //
    class class_symbol_environment RILL_CXX11_FINAL
        : public environment_base
    {
    public:
        static kind::type_value const KindValue;

    public:
        class_symbol_environment(
            environment_parameter_t&& pp,
            environment_id_t const& wrapper_set_env_id,
            native_string_type const& base_name
            )
            : environment_base( std::move( pp ) )
            , base_name_( base_name )
            , decl_attr_( attribute::decl::k_default )
            , builtin_kind_( class_builtin_kind::k_none )
        {}

    public:
        auto get_symbol_kind() const
            -> kind::type_value override
        {
            return KindValue;
        }

        auto complete(
            native_string_type const& mangled_name,
            attribute::decl::type const& decl_attr = attribute::decl::k_default
            )
            -> void
        {
            mangled_name_ = mangled_name;
            set_attribute( decl_attr );

            change_progress_to_completed();
        }

        auto get_base_name() const
            -> native_string_type const&
        {
            return base_name_;
        }

        auto get_mangled_name() const
            -> native_string_type const&
        {
            return mangled_name_;
        }

        bool has_attribute( attribute::decl::type const& attribute ) const
        {
            return ( decl_attr_ & attribute  ) != 0;
        }

        void set_attribute( attribute::decl::type const& attribute )
        {
            decl_attr_ |= attribute;
        }

        void unset_attribute( attribute::decl::type const& attribute )
        {
            decl_attr_ ^= attribute;
        }

        auto set_builtin_kind( class_builtin_kind const& kind )
        {
            builtin_kind_ = kind;
        }

        auto get_builtin_kind() const
            -> class_builtin_kind const&
        {
            return builtin_kind_;
        }

        auto dump( std::ostream& os, std::string const& indent ) const
            -> std::ostream& RILL_CXX11_OVERRIDE
        {
            os  << indent << "class_symbol_environment" << std::endl;
            return dump_include_env( os, indent );
        }

    public:
        auto make_type_id_from(
            attribute::type_attributes const& type_attr = attribute::make_value_default()
            ) const
            -> shared_resource_type::type_registry_type::type_id_type
        {
            return make_type_id(
                cast_to<class_symbol_environment const>( shared_from_this() ),
                type_attr
                );
        }

        auto make_as_array(
            type_id_t const& inner_type_id,
            std::size_t const& elements_num
            )
            -> void
        {
            assert( pointer_detail_ == nullptr );
            array_detail_ = std::make_shared<array_detail>( inner_type_id, elements_num );
        }

        auto is_array() const
            -> bool
        {
            return array_detail_ != nullptr;
        }

        auto make_as_pointer(
            type_id_t const& inner_type_id
            )
            -> void
        {
            assert( array_detail_ == nullptr );
            pointer_detail_ = std::make_shared<pointer_detail>( inner_type_id );
        }

        auto is_pointer() const
            -> bool
        {
            return pointer_detail_ != nullptr;
        }

    public:
        struct array_detail
        {
            array_detail(
                type_id_t const& i,
                std::size_t const& e
                )
                : inner_type_id( i )
                , elements_num( e )
            {}

            type_id_t inner_type_id;
            std::size_t elements_num;
        };

        auto get_array_detail() const
            -> std::shared_ptr<array_detail const>
        {
            return array_detail_;
        }

    public:
        struct pointer_detail
        {
            pointer_detail(
                type_id_t const& i
                )
                : inner_type_id( i )
            {}

            type_id_t inner_type_id;
        };

        auto get_pointer_detail() const
            -> std::shared_ptr<pointer_detail const>
        {
            return pointer_detail_;
        }

    private:
        native_string_type base_name_, mangled_name_;
        attribute::decl::type decl_attr_;
        class_builtin_kind builtin_kind_;

        std::shared_ptr<array_detail> array_detail_;
        std::shared_ptr<pointer_detail> pointer_detail_;
    };

} // namespace rill
