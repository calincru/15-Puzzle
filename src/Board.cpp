// Copyright (C) 2014 Călin Cruceru
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

// Self
#include "Board.h"

// Standard Library
#include <cassert>
#include <cstdlib>
#include <cmath>


namespace Puzzle8
{

void swap(Board &first, Board &second) throw()
{
    std::swap(first.m_blocks, second.m_blocks);
}

Board::Board()
    : m_size(0)
{
    // nothing to do
}

Board::Board(const Board &other)
{
    m_blocks = other.m_blocks;
    m_size = other.m_size;
}

Board::Board(const std::vector<int> &initBlocks, int dim)
    : m_blocks(initBlocks),
      m_size(dim)
{
    // nothing to do
}

Board::~Board()
{
    // nothing to do
}

Board &Board::operator=(Board other)
{
    swap(*this, other);
    return *this;
}

bool Board::operator==(const Board &other) const
{
    assert(m_blocks.size() == other.m_blocks.size());
    return m_blocks == other.m_blocks && m_size == other.m_size;
}

bool Board::operator!=(const Board &other) const
{
    return !this->operator==(other);
}

int Board::dimension() const
{
    return m_size;
}

int Board::hamming() const
{
    int count = 0;
    for (std::vector<int>::const_iterator it = m_blocks.cbegin();
         it != m_blocks.cend(); ++it)
        count += (*it == it - m_blocks.cbegin() + 1 ? 1 : 0);

    return count;
}

int Board::manhattan() const
{
    int count = 0;
    for (std::vector<int>::const_iterator it = m_blocks.cbegin();
         it != m_blocks.cend(); ++it) {
        int i = (it - m_blocks.cbegin())/m_size;
        int j = it - m_blocks.cbegin() - i*m_size;
        int goalRow = (*it - 1)/m_size;
        int goalColumn = *it - goalRow*m_size - 1;

        count += (abs(goalRow - i) + abs(goalColumn - j));
    }

    return count;
}

bool Board::isGoal() const
{
    for (std::vector<int>::const_iterator it = m_blocks.cbegin();
         it != m_blocks.cend() - 1; ++it)
        if (*it != it - m_blocks.cbegin() + 1)
            return false;

    assert(m_blocks.back() == 0);
    return true;
}

Board Board::twin() const
{
    // more intelligent choice of the twin?
    Board twinBoard = *this;
    if (!m_blocks.front()) {
        int tmp = m_blocks[2];
        twinBoard.m_blocks[2] = m_blocks[1];
        twinBoard.m_blocks[1] = tmp;
    } else if (!m_blocks[1]) {
        int tmp = m_blocks[m_size];
        twinBoard.m_blocks[m_size] = m_blocks[m_size+1];
        twinBoard.m_blocks[m_size+1] = tmp;
    } else {
        int tmp = m_blocks.front();
        twinBoard.m_blocks.front() = m_blocks[1];
        twinBoard.m_blocks[1] = tmp;
    }

    return twinBoard;
}

Queue<Board> Board::neighbours() const
{
    Queue<Board> neighList;
    int emptyRow, emptyColumn;
    emptyPosition(emptyRow, emptyColumn);

    if (emptyRow > 0)
        neighList.enqueue(upperNeighbour(emptyRow, emptyColumn));
    if (emptyRow < m_size - 1)
        neighList.enqueue(lowerNeighbour(emptyRow, emptyColumn));
    if (emptyColumn > 0)
        neighList.enqueue(leftNeighbour(emptyRow, emptyColumn));
    if (emptyColumn < m_size - 1)
        neighList.enqueue(rightNeighbour(emptyRow, emptyColumn));

    return neighList;
}

std::string Board::toString() const
{
    std::string result;
    for (std::vector<int>::const_iterator it = m_blocks.cbegin();
         it != m_blocks.cend(); ++it) {
        int i = (it - m_blocks.cbegin())/m_size;
        int j = it - m_blocks.cbegin() - i*m_size;

        result += std::to_string(*it);
        if (j < m_size - 1)
            result += " ";
        else
            result += "\n";
    }

    return result;
}

void Board::emptyPosition(int &emptyRow, int &emptyColumn) const
{
    for (std::vector<int>::const_iterator it = m_blocks.cbegin();
         it != m_blocks.cend(); ++it)
        if (!*it) {
            emptyRow = (it - m_blocks.cbegin())/m_size;
            emptyColumn = it - m_blocks.cbegin() - emptyRow*m_size;
            return;
        }

    assert(0);
}

Board Board::upperNeighbour(int emptyRow, int emptyColumn) const
{
    assert(emptyRow > 0);
    assert(emptyColumn >= 0 && emptyColumn < m_size);

    Board newBoard = *this;
    int prevValue = m_blocks[(emptyRow-1)*m_size + emptyColumn];
    newBoard.m_blocks[(emptyRow-1)*m_size + emptyColumn] = 0;
    newBoard.m_blocks[emptyRow*m_size + emptyColumn] = prevValue;
    return newBoard;
}

Board Board::lowerNeighbour(int emptyRow, int emptyColumn) const
{
    assert(emptyRow < m_size - 1);
    assert(emptyColumn >= 0 && emptyColumn < m_size);

    Board newBoard = *this;
    int prevValue = m_blocks[(emptyRow+1)*m_size + emptyColumn];
    newBoard.m_blocks[(emptyRow+1)*m_size + emptyColumn] = 0;
    newBoard.m_blocks[emptyRow*m_size + emptyColumn] = prevValue;
    return newBoard;
}

Board Board::leftNeighbour(int emptyRow, int emptyColumn) const
{
    assert(emptyRow >= 0 && emptyRow < m_size);
    assert(emptyColumn > 0);

    Board newBoard = *this;
    int prevValue = m_blocks[emptyRow*m_size + emptyColumn - 1];
    newBoard.m_blocks[emptyRow*m_size + emptyColumn - 1] = 0;
    newBoard.m_blocks[emptyRow*m_size + emptyColumn] = prevValue;
    return newBoard;
}

Board Board::rightNeighbour(int emptyRow, int emptyColumn) const
{
    assert(emptyRow >= 0 && emptyRow < m_size);
    assert(emptyColumn < m_size - 1);

    Board newBoard = *this;
    int prevValue = m_blocks[emptyRow*m_size + emptyColumn + 1];
    newBoard.m_blocks[emptyRow*m_size + emptyColumn + 1] = 0;
    newBoard.m_blocks[emptyRow*m_size + emptyColumn] = prevValue;
    return newBoard;
}

}
