#include <raylib.h>

#include <jank/runtime/context.hpp>
#include <jank/runtime/convert.hpp>
#include <jank/runtime/core/make_box.hpp>
#include <jank/runtime/object.hpp>
#include <jank/runtime/obj/opaque_box.hpp>
#include <jank/runtime/obj/transient_array_map.hpp>

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

  template <>
  struct convert<Image>
  {
    static obj::opaque_box_ref into_object(Image const &image)
    {
      static auto const canonical_type(jtl::immutable_string("Image*"));

      if (!IsImageValid(image))
      {
        throw std::runtime_error{"Invalid Image provided."};
      }

      jtl::ptr<void> data{const_cast<Image *>(new (UseGC) Image(image))};
      return make_box<obj::opaque_box>(data, canonical_type);
    }

    static Image from_object(object_ref const o)
    {
      auto const box(try_object<obj::opaque_box>(o));
      if (box->canonical_type != "Image*")
      {
        throw std::runtime_error{"Box does not contain `Image*`."};
      }
      return *(static_cast<Image *>((void *)box->data));
    }
  };

  template <>
  struct convert<Texture2D>
  {
    static obj::opaque_box_ref into_object(Texture2D const &texture)
    {
      static auto const canonical_type(jtl::immutable_string("Texture2D*"));

      if (!IsTextureValid(texture))
      {
        throw std::runtime_error{"Invalid Texture2D provided."};
      }

      jtl::ptr<void> data{const_cast<Texture2D *>(new (UseGC) Texture2D(texture))};
      return make_box<obj::opaque_box>(data, canonical_type);
    }

    static Texture2D from_object(object_ref const o)
    {
      auto const box(try_object<obj::opaque_box>(o));
      if (box->canonical_type != "Texture2D*")
      {
        throw std::runtime_error{"Box does not contain `Texture2D*`."};
      }
      return *(static_cast<Texture2D *>((void *)box->data));
    }
  };

}