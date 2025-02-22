
using System;
using System.Collections.Generic;
using System.Linq;

namespace ConsoleApp2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            try
            {
                Triangle triangle = new Triangle(3, 4, 5);
                Console.WriteLine($"Triangle: Area = {triangle.Area}, Perimeter = {triangle.Perimeter}");

                Square square = new Square(5);
                Console.WriteLine($"Square: Area = {square.Area}, Perimeter = {square.Perimeter}");

                Rectangle rectangle = new Rectangle(4, 6);
                Console.WriteLine($"Rectangle: Area = {rectangle.Area}, Perimeter = {rectangle.Perimeter}");

                Circle circle = new Circle(3);
                Console.WriteLine($"Circle: Area = {circle.Area}, Perimeter = {circle.Perimeter}");

                CompositeFigure composite = new CompositeFigure();
                composite.AddFigure(triangle);
                composite.AddFigure(square);
                Console.WriteLine($"Composite Figure: Area = {composite.Area}, Perimeter = {composite.Perimeter}");
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }

            Console.ReadKey();
        }
    }
    public abstract class GeometricFigure
    {
        public double Area { get; protected set; }
        public double Perimeter { get; protected set; }

        public abstract void CalculateArea();
        public abstract void CalculatePerimeter();
    }

    public interface SimplePolygon
    {
        double Height { get; }
        double Base { get; }
        double AngleBetweenBaseAndSide { get; }
        int SidesCount { get; }
        double[] SideLengths { get; }
        double Area { get; }
        double Perimeter { get; }
    }

    public class Triangle : GeometricFigure, SimplePolygon
    {
        public double SideA { get; }
        public double SideB { get; }
        public double SideC { get; }

        public Triangle(double a, double b, double c)
        {
            if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a)
            {
                throw new ArgumentException("Invalid triangle sides.");
            }

            SideA = a;
            SideB = b;
            SideC = c;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            double s = (SideA + SideB + SideC) / 2;
            Area = Math.Sqrt(s * (s - SideA) * (s - SideB) * (s - SideC));
        }

        public override void CalculatePerimeter()
        {
            Perimeter = SideA + SideB + SideC;
        }

        public double Height => CalculateHeight();
        public double Base => SideC;
        public double AngleBetweenBaseAndSide => CalculateAngle();
        public int SidesCount => 3;
        public double[] SideLengths => new[] { SideA, SideB, SideC };

        private double CalculateHeight()
        {
            return 2 * Area / Base;
        }

        private double CalculateAngle()
        {
            return Math.Acos((SideA * SideA + SideC * SideC - SideB * SideB) / (2 * SideA * SideC));
        }
    }

    public class Square : GeometricFigure, SimplePolygon
    {
        public double Side { get; }

        public Square(double side)
        {
            if (side <= 0)
            {
                throw new ArgumentException("Invalid side length.");
            }

            Side = side;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = Side * Side;
        }

        public override void CalculatePerimeter()
        {
            Perimeter = 4 * Side;
        }

        public double Height => Side;
        public double Base => Side;
        public double AngleBetweenBaseAndSide => Math.PI / 2;
        public int SidesCount => 4;
        public double[] SideLengths => new[] { Side, Side, Side, Side };
    }

    public class Rectangle : GeometricFigure, SimplePolygon
    {
        public double Width { get; }
        public double HeightValue { get; }

        public Rectangle(double width, double height)
        {
            if (width <= 0 || height <= 0)
            {
                throw new ArgumentException("Invalid width or height.");
            }

            Width = width;
            HeightValue = height;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = Width * HeightValue;
        }

        public override void CalculatePerimeter()
        {
            Perimeter = 2 * (Width + HeightValue);
        }

        public double Height => HeightValue;
        public double Base => Width;
        public double AngleBetweenBaseAndSide => Math.PI / 2;
        public int SidesCount => 4;
        public double[] SideLengths => new[] { Width, HeightValue, Width, HeightValue };
    }

    public class Rhombus : GeometricFigure, SimplePolygon
    {
        public double Side { get; }
        public double Angle { get; }

        public Rhombus(double side, double angle)
        {
            if (side <= 0 || angle <= 0 || angle >= Math.PI)
            {
                throw new ArgumentException("Invalid side or angle.");
            }

            Side = side;
            Angle = angle;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = Side * Side * Math.Sin(Angle);
        }

        public override void CalculatePerimeter()
        {
            Perimeter = 4 * Side;
        }

        public double Height => Side * Math.Sin(Angle);
        public double Base => Side;
        public double AngleBetweenBaseAndSide => Angle;
        public int SidesCount => 4;
        public double[] SideLengths => new[] { Side, Side, Side, Side };
    }

    public class Parallelogram : GeometricFigure, SimplePolygon
    {
        public double SideA { get; }
        public double SideB { get; }
        public double Angle { get; }

        public Parallelogram(double a, double b, double angle)
        {
            if (a <= 0 || b <= 0 || angle <= 0 || angle >= Math.PI)
            {
                throw new ArgumentException("Invalid sides or angle.");
            }

            SideA = a;
            SideB = b;
            Angle = angle;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = SideA * SideB * Math.Sin(Angle);
        }

        public override void CalculatePerimeter()
        {
            Perimeter = 2 * (SideA + SideB);
        }

        public double Height => SideB * Math.Sin(Angle);
        public double Base => SideA;
        public double AngleBetweenBaseAndSide => Angle;
        public int SidesCount => 4;
        public double[] SideLengths => new[] { SideA, SideB, SideA, SideB };
    }

    public class Trapezoid : GeometricFigure, SimplePolygon
    {
        public double BaseA { get; }
        public double BaseB { get; }
        public double HeightValue { get; }

        public Trapezoid(double a, double b, double height)
        {
            if (a <= 0 || b <= 0 || height <= 0)
            {
                throw new ArgumentException("Invalid bases or height.");
            }

            BaseA = a;
            BaseB = b;
            HeightValue = height;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = 0.5 * (BaseA + BaseB) * HeightValue;
        }

        public override void CalculatePerimeter()
        {
           
            throw new NotImplementedException("Perimeter calculation requires side lengths.");
        }

        public double Height => HeightValue;
        public double Base => BaseA; 
        public double AngleBetweenBaseAndSide => throw new NotImplementedException("Angle calculation requires side lengths.");
        public int SidesCount => 4;
        public double[] SideLengths => throw new NotImplementedException("Side lengths are not fully defined.");
    }

    public class Circle : GeometricFigure, SimplePolygon
    {
        public double Radius { get; }

        public Circle(double radius)
        {
            if (radius <= 0)
            {
                throw new ArgumentException("Invalid radius.");
            }

            Radius = radius;
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = Math.PI * Radius * Radius;
        }

        public override void CalculatePerimeter()
        {
            Perimeter = 2 * Math.PI * Radius;
        }

        public double Height => 2 * Radius;
        public double Base => 2 * Radius;
        public double AngleBetweenBaseAndSide => 0; // Круг не имеет углов
        public int SidesCount => 0; // Или бесконечность, зависит от определения
        public double[] SideLengths => new double[0];
    }

    public class Ellipse : GeometricFigure, SimplePolygon
    {
        public double MajorRadius { get; }
        public double MinorRadius { get; }

        public Ellipse(double major, double minor)
        {
            if (major <= 0 || minor <= 0)
            {
                {
                    throw new ArgumentException("Invalid major or minor radius.");
                }

                MajorRadius = major;
                MinorRadius = minor;
                CalculateArea();
                CalculatePerimeter();
            }
        }

        public override void CalculateArea()
        {
            Area = Math.PI * MajorRadius * MinorRadius;
        }

        public override void CalculatePerimeter()
        {
            
            Perimeter = Math.PI * (3 * (MajorRadius + MinorRadius) - Math.Sqrt((3 * MajorRadius + MinorRadius) * (MajorRadius + 3 * MinorRadius)));
        }

        public double Height => 2 * MinorRadius; 
        public double Base => 2 * MajorRadius; 
        public double AngleBetweenBaseAndSide => 0; 
        public int SidesCount => 0; 
        public double[] SideLengths => new double[0];
    }

    public class CompositeFigure : GeometricFigure
    {
        private List<SimplePolygon> _figures = new List<SimplePolygon>();

        public void AddFigure(SimplePolygon figure)
        {
            _figures.Add(figure);
            CalculateArea();
            CalculatePerimeter();
        }

        public override void CalculateArea()
        {
            Area = _figures.Sum(f => f.Area);
        }

        public override void CalculatePerimeter()
        {
            
            Perimeter = _figures.Sum(f => f.Perimeter);
        }
    }
}
          
