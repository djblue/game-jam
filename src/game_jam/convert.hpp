#include <raylib.h>

#include <jank/runtime/context.hpp>
#include <jank/runtime/convert.hpp>
#include <jank/runtime/core/make_box.hpp>
#include <jank/runtime/obj/transient_array_map.hpp>
#include <jank/runtime/object.hpp>

namespace jank::runtime
{
  template <>
  struct convert<Vector2>
  {
    static obj::persistent_array_map_ref into_object(Vector2 const &v)
    {
      static auto const x(__rt_ctx->intern_keyword("x").expect_ok());
      static auto const y(__rt_ctx->intern_keyword("y").expect_ok());

      obj::transient_array_map m{};

      m.assoc_in_place(x, make_box(v.x));
      m.assoc_in_place(y, make_box(v.y));

      return m.to_persistent();
    }

    static Vector2 from_object(object_ref const o)
    {
      static auto const x(__rt_ctx->intern_keyword("x").expect_ok());
      static auto const y(__rt_ctx->intern_keyword("y").expect_ok());
      return Vector2(o.get(x).to_real(), o.get(y).to_real());
    }
  };

  template <>
  struct convert<Color>
  {
    static obj::small_integer_ref into_object(Color const &v)
    {
      return ColorToInt(v);
    }

    static Color from_object(object_ref const o)
    {
      return Color(o.to_integer());
    }
  };
}