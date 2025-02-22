using System;
using System.Collections.Generic;

namespace ConsoleApp2
{
    public abstract class DrawableFigure
    {
        public int X { get; set; }
        public int Y { get; set; }
        public char Symbol { get; set; }
        public ConsoleColor Color { get; set; }

        public abstract void Draw();
    }

    public class DrawableRectangle : DrawableFigure
    {
        public int Width { get; set; }
        public int Height { get; set; }

        public override void Draw()
        {
            Console.ForegroundColor = Color;
            for (int i = 0; i < Height; i++)
            {
                Console.SetCursorPosition(X, Y + i);
                Console.WriteLine(new string(Symbol, Width));
            }
            Console.ResetColor();
        }
    }

    public class DrawableTriangle : DrawableFigure
    {
        public int Size { get; set; }

        public override void Draw()
        {
            Console.ForegroundColor = Color;
            for (int i = 0; i < Size; i++)
            {
                Console.SetCursorPosition(X, Y + i);
                Console.WriteLine(new string(Symbol, 2 * i + 1));
            }
            Console.ResetColor();
        }
    }

    public class DrawableRhombus : DrawableFigure
    {
        public int Size { get; set; }

        public override void Draw()
        {
            Console.ForegroundColor = Color;
            for (int i = 0; i < Size; i++)
            {
                Console.SetCursorPosition(X - i, Y + i);
                Console.WriteLine(new string(' ', Size - i - 1) + new string(Symbol, 2 * i + 1));
            }
            for (int i = Size - 2; i >= 0; i--)
            {
                Console.SetCursorPosition(X - i, Y + 2 * Size - 2 - i);
                Console.WriteLine(new string(' ', Size - i - 1) + new string(Symbol, 2 * i + 1));
            }
            Console.ResetColor();
        }
    }

    public class FigureCollection : IEnumerable<DrawableFigure>
    {
        private List<DrawableFigure> _figures = new List<DrawableFigure>();

        public void AddFigure(DrawableFigure figure)
        {
            _figures.Add(figure);
        }

        public void DrawAllFigures()
        {
            foreach (var figure in _figures)
            {
                figure.Draw();
            }
        }

        public IEnumerator<DrawableFigure> GetEnumerator()
        {
            return _figures.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            FigureCollection collection = new FigureCollection();

            while (true)
            {
                Console.WriteLine("Select a figure:");
                Console.WriteLine("1. Rectangle");
                Console.WriteLine("2. Triangle");
                Console.WriteLine("3. Rhombus");
                Console.WriteLine("4. Exit");

                int choice = int.Parse(Console.ReadLine());

                if (choice == 4)
                {
                    break;
                }

                Console.Write("X: ");
                int x = int.Parse(Console.ReadLine());
                Console.Write("Y: ");
                int y = int.Parse(Console.ReadLine());
                Console.Write("Symbol: ");
                char symbol = Console.ReadKey().KeyChar;
                Console.WriteLine();
                Console.Write("Color (0-15): ");
                ConsoleColor color = (ConsoleColor)int.Parse(Console.ReadLine());

                switch (choice)
                {
                    case 1:
                        Console.Write("Width: ");
                        int width = int.Parse(Console.ReadLine());
                        Console.Write("Height: ");
                        int height = int.Parse(Console.ReadLine());
                        collection.AddFigure(new DrawableRectangle { X = x, Y = y, Symbol = symbol, Color = color, Width = width, Height = height });
                        break;
                    case 2:
                        Console.Write("Size: ");
                        int triangleSize = int.Parse(Console.ReadLine());
                        collection.AddFigure(new DrawableTriangle { X = x, Y = y, Symbol = symbol, Color = color, Size = triangleSize });
                        break;
                    case 3:
                        Console.Write("Size: ");
                        int rhombusSize = int.Parse(Console.ReadLine());
                        collection.AddFigure(new DrawableRhombus { X = x, Y = y, Symbol = symbol, Color = color, Size = rhombusSize });
                        break;
                        // Add handling for other figures
                }

                Console.Clear();
                collection.DrawAllFigures();
            }
        }
    }
}
