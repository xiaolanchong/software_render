
#include "PropertyMapImpl.h"

PropertyMapImpl::PropertyMapImpl(const std::string& fileName)
{
   m_values =
   { 
      {prop_geo_dodecahedron_enable, {1.f}},
      
      {prop_geo_dodecahedron_color, {float(0xff00000)}},

      {prop_geo_cylinder_enable, {1.f}},
      {prop_geo_cylinder_color, {float(0x00ff00)}},
      {prop_geo_cylinder_segments, {30.f}},

      {prop_geo_torus_enable, {1.f}},
      {prop_geo_torus_color, {float(0x0000ff)}},
      {prop_geo_torus_rings, {30.f}},
      {prop_geo_torus_segments, {20.f}},

      {prop_geo_wireframe, {0.f}},
      {prop_geo_fill, {0.f}},
      {prop_geo_fill_and_textures, {1.f}},

      {prop_light_lambert, {0.f}},
      {prop_light_gouraud, {0.f}},
      {prop_light_phong, {1.f}},

      {prop_light_direct, {0.f}},
      {prop_light_point, {1.f}},
      {prop_light_spot, {0.f}},

      {prop_light_intensity, {20.f}},
      {prop_light_color, {float(0xffffff)}},
      {prop_light_pos_x, {-5.f}},
      {prop_light_pos_y, {5.f}},
      {prop_light_pos_z, {-5.f}},

      {prop_rs_rotate_x, {0.f}},
      {prop_rs_rotate_y, {15.f}},
      {prop_rs_rotate_z, {0.f}},

      {prop_rs_scale_x, {1.f}},
      {prop_rs_scale_y, {1.f}},
      {prop_rs_scale_z, {1.f}},

   };
}

float PropertyMapImpl::GetNumericProperty(PropertyId id)
{
   auto it = m_values.find(id);
   if (it == m_values.end())
      throw NoSuchProperty(id);

   return std::visit([](auto&& arg)
      {
         using T = std::decay_t<decltype(arg)>;
         if constexpr (std::is_same_v<T, float>)
            return arg;
         else if constexpr (std::is_same_v<T, std::string>)
            return 0.f;
         return 0.f;
      }, it->second);
}

std::string	PropertyMapImpl::GetStringProperty(PropertyId id)
{
   auto it = m_values.find(id);
   if (it == m_values.end())
      return {};
#if 0
   return std::visit(it->second, [](auto&& arg)
      {
         using T = std::decay_t<decltype(arg)>;
         if constexpr (std::is_same_v<T, float>)
            return {};
         else if constexpr (std::is_same_v<T, std::string>)
            return arg;
         return {};
      });
#endif
   throw NoSuchProperty(id);
}
