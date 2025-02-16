#include "RacingTrack.h"
#include "TrackPiece.h"

RacingTrack::RacingTrack(const std::vector<std::shared_ptr<TrackPiece>>& track_pieces) :
    track_pieces_{track_pieces}
{
}

const std::vector<std::shared_ptr<TrackPiece>>& RacingTrack::get_track_pieces() const
{
    return track_pieces_;
}
