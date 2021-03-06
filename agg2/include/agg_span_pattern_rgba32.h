//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.2
// Copyright (C) 2002-2004 Maxim Shemanarev (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------


#ifndef AGG_SPAN_PATTERN_RGBA32_INCLUDED
#define AGG_SPAN_PATTERN_RGBA32_INCLUDED

#include "agg_basics.h"
#include "agg_pixfmt_rgba32.h"
#include "agg_span_pattern.h"

namespace agg
{

    //======================================================span_pattern_rgba32
    template<class Order, class Allocator = span_allocator<rgba8> >
    class span_pattern_rgba32 : public span_pattern<rgba8, int8u, Allocator>
    {
    public:
        typedef Allocator alloc_type;
        typedef rgba8 color_type;
        typedef span_pattern<color_type, int8u, alloc_type> base_type;

        //--------------------------------------------------------------------
        span_pattern_rgba32(alloc_type& alloc) : base_type(alloc) {}

        //----------------------------------------------------------------
        span_pattern_rgba32(alloc_type& alloc,
                            const rendering_buffer& src, 
                            unsigned offset_x, unsigned offset_y) :
            base_type(alloc, src, offset_x, offset_y, 0)
        {}

        //--------------------------------------------------------------------
        color_type* generate(int x, int y, unsigned len)
        {   
            color_type* span = base_type::allocator().span();
            unsigned sx = (base_type::offset_x() + x) % base_type::source_image().width();
            unsigned wp = base_type::source_image().width() << 2;
            const int8u* p = base_type::source_image().row((base_type::offset_y() + y) % base_type::source_image().height());
            p += sx << 2;
            do
            {
                span->r = p[Order::R];
                span->g = p[Order::G];
                span->b = p[Order::B];
                span->a = p[Order::A];
                p += 4;
                ++sx;
                ++span;
                if(sx >= base_type::source_image().width())
                {
                    sx -= base_type::source_image().width();
                    p -= wp;
                }
            }
            while(--len);
            return base_type::allocator().span();
        }
    };

}

#endif

