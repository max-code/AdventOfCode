#include "../util/util.h"

enum class Pipe
{
    VERTICAL = '|',
    HORIZONTAL = '-',
    NORTH_EAST = 'L',
    NORTH_WEST = 'J',
    SOUTH_EAST = 'F',
    SOUTH_WEST = '7',
    START = 'S',
    BLANK = '.'
};

enum class Direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

Pipe charToPipe(const char& c) {
    switch (c) {
    case '|': return Pipe::VERTICAL;
    case '-': return Pipe::HORIZONTAL;
    case 'L': return Pipe::NORTH_EAST;
    case 'J': return Pipe::NORTH_WEST;
    case 'F': return Pipe::SOUTH_EAST;
    case '7': return Pipe::SOUTH_WEST;
    case 'S': return Pipe::START;
    case '.': return Pipe::BLANK;
    }
}

char pipeToChar(Pipe pipe) {
    switch (pipe) {
    case Pipe::VERTICAL: return '|';
    case Pipe::HORIZONTAL: return '-';
    case Pipe::NORTH_EAST: return 'L';
    case Pipe::NORTH_WEST: return 'J';
    case Pipe::SOUTH_EAST: return 'F';
    case Pipe::SOUTH_WEST: return '7';
    case Pipe::START: return 'S';
    case Pipe::BLANK: return '.';
    }
}

char dirToChar(Direction d) {
    switch (d) {
    case Direction::WEST: return 'W';
    case Direction::SOUTH: return 'S';
    case Direction::EAST: return 'E';
    case Direction::NORTH: return 'N';
    }
}

struct Point {
    int x, y;
    // Overload '==' operator
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // Overload '!=' operator
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};



bool validMove(Pipe from, Pipe to, Direction direction)
{
    if (to == Pipe::BLANK) return false;

    if (direction == Direction::NORTH)
    {
        if (to == Pipe::VERTICAL || to == Pipe::SOUTH_EAST || to == Pipe::SOUTH_WEST || to == Pipe::START)
        {
            if (from == Pipe::VERTICAL || from == Pipe::NORTH_EAST || from == Pipe::NORTH_WEST || from == Pipe::START) return true;
        }
    }
    else if (direction == Direction::SOUTH)
    {
        if (to == Pipe::VERTICAL || to == Pipe::NORTH_EAST || to == Pipe::NORTH_WEST || to == Pipe::START)
        {
            if (from == Pipe::VERTICAL || from == Pipe::SOUTH_EAST || from == Pipe::SOUTH_WEST || from == Pipe::START) return true;
        }
    }
    else if (direction == Direction::EAST)
    {
        if (to == Pipe::HORIZONTAL || to == Pipe::NORTH_WEST || to == Pipe::SOUTH_WEST || to == Pipe::START)
        {
            if (from == Pipe::HORIZONTAL || from == Pipe::NORTH_EAST || from == Pipe::SOUTH_EAST || from == Pipe::START) return true;
        }
    }
    else if (direction == Direction::WEST)
    {
        if (to == Pipe::HORIZONTAL || to == Pipe::NORTH_EAST|| to == Pipe::SOUTH_EAST|| to == Pipe::START)
        {
            if (from == Pipe::HORIZONTAL || from == Pipe::NORTH_WEST|| from == Pipe::SOUTH_WEST || from == Pipe::START) return true;
        }
    }

    return false;

}


void makeValidMove(const std::vector<std::vector<Pipe>>& field, Point& currentPos, Point& lastPos)
{
    std::vector<std::tuple<int, int, Direction>> moves = { {1, 0, Direction::SOUTH},{-1, 0, Direction::NORTH},{0, 1, Direction::EAST}, {0, -1, Direction::WEST} };

    for (auto [y, x, d] : moves)
    {
        int newY = currentPos.y + y, newX = currentPos.x + x;
        if (newY == lastPos.y && newX == lastPos.x) continue; // Dont move backwards

        if (validMove(field[currentPos.y][currentPos.x], field[newY][newX], d))
        {
            lastPos = currentPos;
            currentPos = Point(newX, newY);
            return;
        }
    }
}

// Copyright @ Chad Petey
bool onBoundary(const Point& point, const Point& p1, const Point& p2) {
    // Check if point is on the line segment between p1 and p2
    if (std::min(p1.x, p2.x) <= point.x && point.x <= std::max(p1.x, p2.x) &&
        std::min(p1.y, p2.y) <= point.y && point.y <= std::max(p1.y, p2.y)) {
        double crossProduct = (point.y - p1.y) * (p2.x - p1.x) - (point.x - p1.x) * (p2.y - p1.y);
        if (std::abs(crossProduct) < 1e-6) { // Consider a tolerance for floating-point comparison
            return true;
        }
    }
    return false;
}

// Copyright @ Chad Petey
bool isPointInsidePolygon(const Point& point, const std::vector<Point>& polygon) {
    int count = 0;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n];

        // Check if the point is on the polygon boundary
        if (onBoundary(point, p1, p2)) {
            return false; // Exclude points on the boundary
        }

        // Check for intersections with polygon edges
        if (point.y > std::min(p1.y, p2.y) && point.y <= std::max(p1.y, p2.y) && point.x <= std::max(p1.x, p2.x) && p1.y != p2.y) {
            double xinters = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
            if (p1.x == p2.x || point.x < xinters) {
                count++;
            }
        }
    }
    return count % 2 != 0;
}

std::vector<Point> findPath(const std::vector<std::string>& lines)
{
    std::vector<std::vector<Pipe>> field;
    Point startPos{};
    field.push_back(std::vector<Pipe>(lines[0].size() + 1, Pipe::BLANK)); // Padding

    for (int y = 0; y < lines.size(); y++)
    {
        const std::string& line = lines[y];
        std::vector<Pipe> pipes{ Pipe::BLANK } // Start with padding
        ;
        for (int x = 0; x < line.size(); x++) {
            pipes.push_back(charToPipe(line[x]));

            if (line[x] == 'S')
            {
                startPos.x = x + 1;
                startPos.y = y + 1;
            }
        }
        pipes.push_back(Pipe::BLANK); // Padding
        field.push_back(pipes);
    }
    field.push_back(std::vector<Pipe>(lines[0].size() + 2, Pipe::BLANK)); // Padding


    Point currentPos = startPos, lastPos = startPos;

    std::vector<Point> path;

    do {
        path.push_back(currentPos);
        makeValidMove(field, currentPos, lastPos);
    } while (currentPos != startPos);

    return path;
}


// Part 1 function
void part1(std::vector<std::string>& lines) 
{
    std::vector<Point> path = findPath(lines);
    std::cout << path.size() / 2 << std::endl;

}

// Part 2 function
void part2(const std::vector<std::string>& lines) 
{

    std::vector<Point> path = findPath(lines);
    int height = lines.size() + 2; // +2 accounts for padding, which lets us avoid bounds checking
    int width = lines[0].size() + 2;


    int inside = 0;

    for (int y = 2; y<height-2; y++)
    {
        for (int x = 2; x<width-2; x++)
        {
            if (isPointInsidePolygon(Point(x, y), path)) inside++;
        }
    }
    std::cout << inside << std::endl;

}

int main() {
    std::vector<std::string> lines = aoc_util::string::readFile<aoc_util::string::MultipleLines>("C:\\Users\\maxjo\\source\\repos\\AdventOfCode\\2023\\day10\\input.txt");

    aoc_util::time::timeCall<std::chrono::microseconds>("part1", part1, lines); // 6951
    aoc_util::time::timeCall<std::chrono::microseconds>("part2", part2, lines); // 563
    return 0;
}
