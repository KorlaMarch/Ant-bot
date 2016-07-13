#ifndef LOCATION_H_
#define LOCATION_H_

/*
    struct for representing locations in the grid.
*/
struct Location
{
    int row, col;

    Location()
    {
        row = col = 0;
    };

    Location(int r, int c)
    {
        row = r;
        col = c;
    };

    bool operator<( const Location loc ) const {
        if ( row != loc.row ) {
            return row < loc.row;
        }
        return col < loc.col;
    }

    bool operator==( const Location loc ) const {
        return row == loc.row and col == loc.col;
    }

    bool operator!=( const Location loc ) const {
        return not ( *this == loc );
    }
};

#endif //LOCATION_H_
