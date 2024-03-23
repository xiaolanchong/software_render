#pragma once

//struct _TRIVERTEX;
//class CPoint;

class IDeviceContext
{
public:
   struct Point
   {
      int x, y;
   };
   struct PointAndColor
   {
      Point pt;
      std::uint8_t r, g, b;
   };

   static constexpr size_t VERTICES_IN_TRIANGLE = 3;

   virtual ~IDeviceContext() = default;

#if 0
   virtual bool GradientFill(const _TRIVERTEX* pVertex, size_t nVertex, const void* pMesh, size_t nMesh) = 0;
#else
   virtual bool DrawGradientTriangles(const PointAndColor* pVertex, size_t nVertex) = 0;
#endif

   /// <summary>
   /// Draws a series of transparent triangles
   /// </summary>
   /// <param name="lpPoints">Pointer to array of vertices, the size is 3 * nTriangleCount</param>
   /// <param name="nTriangleCount">number of the triangles in <c>lpPoints</c></param>
   /// <returns>true - succeeded, false - failed</returns>
   virtual bool DrawEmptyTriangles(const Point* pVertex, size_t nTriangleCount) = 0;

   /// <summary>
   /// Draws a bit image
   /// </summary>
   /// <param name="w">width of the image</param>
   /// <param name="h">height of the image</param>
   /// <param name="image">array of 4 bytes pixels, 8 bytes of GBR, the size is 4 * w * h, from top left to bottom right</param>
   /// <returns>true - succeeded, false - failed</returns>
   virtual bool BitBlt(unsigned int w, unsigned int h, const void* image) = 0;
};

