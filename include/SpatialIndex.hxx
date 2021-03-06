//#     Filename:       SpatialIndex.hxx
//#
//#     H Implementations for spatialindex
//#
//#     Author:         Peter Z. Kunszt, based on A. Szalay s code
//#
//#     Date:           October 15, 1998
//#
//#		Copyright (C) 2000  Peter Z. Kunszt, Alex S. Szalay, Aniruddha R. Thakar
//#                     The Johns Hopkins University
//#

/////////////leafCount//////////////////////////////////////
/** leafCount: return number of leaf nodes
 *
 * This may be much greater than the number of storedleaves_.
 *
 * @return leaves_ the number of leaves at maxlevel_, the bottom of the index.
 */
inline uint64
SpatialIndex::leafCount() const
{
  return leaves_;
}

/////////////NVERTICES////////////////////////////////////
// nVertices: return number of vertices
inline size_t
SpatialIndex::nVertices() const
{
  //dcdtmp return vertices_.length();
	return vertices_.size();
}

//////////////////LEAFNUMBERBYID///////////////////////////////////////////
// // TODO This just seems wrong.  Maybe for stuff stored after the leaves.
/**
 *
 * This is part of the legacy code that is not really helpful since Bitlists are
 * not used in the code anymore. Since id is being used as an index into
 * an array, this means that we're not looking at an HTM-ID since the
 * depth bit screws up its use as an array index.
 *
 * @param id <em>Not an HTM-ID</em>
 * @return The leafNumberInBitlist = id - leafCount();
 */
inline uint64
SpatialIndex::leafNumberById(uint64 id) const{
//	NOTE BitList no longer exists.
//  if(maxlevel_ > HTMMAXBIT)
//    throw SpatialInterfaceError("SpatialIndex:leafNumberById","BitList may only be used up to level HTMMAXBIT deep");
//	std::cout << "-leafNumberById,id,lc: " << id << " " << leafCount() << std::endl << std::flush;
	return (uint64)(id - leafCount());
}

//////////////////IDBYLEAFNUMBER///////////////////////////////////////////
//
// TODO id by leaf number? leafCount == leaves_ which is the total number of leaves.
inline uint64
SpatialIndex::idByLeafNumber(uint64 n) const{
  uint64 l = leafCount();
  l += n;
  return l;
}

//////////////////NAMEBYLEAFNUMBER////////////////////////////////////////
//
inline char *
SpatialIndex::nameByLeafNumber(uint64 n, char * name) const{
  return nameById(idByLeafNumber(n), name);
}

//////////////////IDBYPOINT////////////////////////////////////////////////
// Find a leaf node where a ra/dec points to
//

inline uint64
SpatialIndex::idByPoint(const float64 & ra, const float64 & dec) const {
  SpatialVector v(ra,dec);
  return idByPoint(v);
}

inline uint64
SpatialIndex::idByLatLon(const float64 &lat, const float64 &lon) const {
	SpatialVector v;
	v.setLatLonDegrees(lat,lon);
	return idByPoint(v);
}

//////////////////NAMEBYPOINT//////////////////////////////////////////////
// Find a leaf node where a ra/dec points to, return its name
//

inline char*
SpatialIndex::nameByPoint(const float64 & ra, const float64 & dec, 
			  char* name) const {
  return nameById(idByPoint(ra,dec), name);
}

//////////////////NAMEBYPOINT//////////////////////////////////////////////
// Find a leaf node where v points to, return its name
//

inline char*
SpatialIndex::nameByPoint(SpatialVector & vector, char* name) const {
  return nameById(idByPoint(vector),name);
}
////////////////////// setMaxlevel /////////////////////////
inline void
SpatialIndex::setMaxlevel(size_t level) {
	this->maxlevel_ = level;
}
