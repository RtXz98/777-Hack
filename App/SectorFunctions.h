static const NSUInteger gridSectors = 6;
static const CGFloat gridSectorLength = 128.f;
static const CGFloat gridSectorCenter = gridSectorLength / 2.f;
static const CGFloat gridLength = gridSectorLength * gridSectors;


static inline CGSize nodeSize() {
  return CGSizeMake(90,90);
}

typedef struct {
  NSUInteger row;
  NSUInteger col;
} Sector;

static inline Sector SectorMake(NSUInteger row, NSUInteger col) {
  return (Sector) {row, col};
}

static inline Sector SectorMakeFromArray(NSArray *array) {
  return SectorMake([[array firstObject] integerValue],
                    [[array lastObject] integerValue]);
}

static inline NSInteger sectorToCoordinate(NSUInteger sectorSegment) {
  return sectorSegment * gridSectorLength + gridSectorCenter;
}

static inline NSInteger coordinateToSector(NSUInteger coordinate) {
  return (coordinate - gridSectorCenter) / gridSectorLength;
}

static inline CGPoint CGPointFromSector(Sector sector) {
  return CGPointMake(sectorToCoordinate(sector.col),sectorToCoordinate(sector.row));
}

static inline Sector SectorFromCGPoint(CGPoint point) {
  return SectorMake(coordinateToSector(point.y), coordinateToSector(point.x));
}

static inline BOOL SectorEqualToSector(Sector sector1, Sector sector2) {
  return sector1.col == sector2.col && sector1.row == sector2.row;
}

static inline BOOL SectorIsAdjacentToSector(Sector sector1, Sector sector2) {
  return abs(sector1.row - sector2.row) <= 1 && abs(sector1.col - sector2.col) <= 1;
}

static inline BOOL SectorIsWithinBoard(Sector sector) {
  return sector.col < gridSectors && sector.row < gridSectors;
}

static inline Sector SectorInDirection(Sector sector, UISwipeGestureRecognizerDirection direction) {
  switch (direction) {
    case UISwipeGestureRecognizerDirectionRight:
      sector.col += 1;
      break;
    case UISwipeGestureRecognizerDirectionLeft:
      sector.col -= 1;
      break;
    case UISwipeGestureRecognizerDirectionUp:
      sector.row += 1;
      break;
    case UISwipeGestureRecognizerDirectionDown:
      sector.row -= 1;
      break;
  }
  return sector;
}

#define SectorZero SectorMake(0,0)
#define log_sector(sec)  NSLog(@"row: %d, col: %d", sec.row, sec.col);
