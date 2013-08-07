//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <rill/semantic_analysis/list_identifier_visitor.hpp>
#include <rill/semantic_analysis/invoke.hpp>

#include <rill/environment.hpp>

#include <rill/statement.hpp>
#include <rill/expression.hpp>
#include <rill/value.hpp>


namespace rill
{
    namespace semantic_analysis
    {
        // statement_list
        void determine_parameter_signature_visitor::operator()( statement_list const& ss, environment_ptr const& env ) const
        {
            for( auto const& s : ss )
                s->dispatch( *this, env );
        }
        
        void determine_parameter_signature_visitor::operator()( expression_statement const& s, environment_ptr const& env ) const
        {
        }
        void determine_parameter_signature_visitor::operator()( return_statement const& s, environment_ptr const& env ) const
        {
        }

        //
        void determine_parameter_signature_visitor::operator()( function_definition_statement const& s, environment_ptr const& env ) const
        {
            // TODO IDENTIFIER
            //s.return_type_
            //env->pre_construct( kind::function_k, s.get_identifier()->get_last_identifier() );
        }

        //
        void determine_parameter_signature_visitor::operator()( class_definition_statement const& s, environment_ptr const& env ) const
        {
        }
        
        // expression
        auto determine_parameter_signature_visitor::operator()( binary_operator_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

        auto determine_parameter_signature_visitor::operator()( call_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

        auto determine_parameter_signature_visitor::operator()( embedded_function_call_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

        auto determine_parameter_signature_visitor::operator()( term_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }
        
        //
        auto determine_parameter_signature_visitor::operator()( intrinsic_value const& v, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }
        auto determine_parameter_signature_visitor::operator()( variable_value const& s, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }
    }
}





namespace rill
{
    namespace semantic_analysis
    {
        // statement_list
        void list_identifier_visitor::operator()( statement_list const& ss, environment_ptr const& env ) const
        {
            for( auto const& s : ss )
                s->dispatch( *this, env );
        }
        
        void list_identifier_visitor::operator()( expression_statement const& s, environment_ptr const& env ) const
        {
        }
        void list_identifier_visitor::operator()( return_statement const& s, environment_ptr const& env ) const
        {
        }

        //
        void list_identifier_visitor::operator()( function_definition_statement const& s, environment_ptr const& env ) const
        {
            env->pre_construct( kind::function_k, s.get_identifier()->get_last_identifier() );
        }

        //
        void list_identifier_visitor::operator()( class_definition_statement const& s, environment_ptr const& env ) const
        {
        }
        
        // expression
        auto list_identifier_visitor::operator()( binary_operator_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

        auto list_identifier_visitor::operator()( call_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

        auto list_identifier_visitor::operator()( embedded_function_call_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

        auto list_identifier_visitor::operator()( term_expression const& e, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }
        
        //
        auto list_identifier_visitor::operator()( intrinsic_value const& v, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }
        auto list_identifier_visitor::operator()( variable_value const& s, environment_ptr const& env ) const -> environment_ptr
        {
            return nullptr;
        }

    } // namespace semantic_analysis
} // namespace rill