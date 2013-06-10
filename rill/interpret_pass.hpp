#pragma once

#include "tree_visitor_base.hpp"

#include "value.hpp"
#include "statement.hpp"
#include "expression.hpp"

struct runtime_interpret_tag;

template<typename Tag>
struct interpret_pass;

template<>
struct interpret_pass<runtime_interpret_tag>
    : public tree_visitor_base
{
    void operator()( statement_list const& ss, environment_ptr const& env ) const
    {
        for( auto const& s : ss )
            s->dispatch( *this, env );
    }

    void operator()( expression_statement const& s, environment_ptr const& env ) const
    {
        // nothing to do...
    }

    // virtual void operator()( native_function_definition_statement const& s, environment_ptr const& env ) const =0;

    void operator()( class_definition_statement const& s, environment_ptr const& env ) const
    {
        //env->add_class( s );
    }
};