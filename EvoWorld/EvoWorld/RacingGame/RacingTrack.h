#pragma once
#include "../CompoundShape.h"
#include "TrackPiece.h"

class RacingTrack
{
public:
    explicit RacingTrack(const std::vector<std::shared_ptr<TrackPiece>>& track_pieces);

    [[nodiscard]] const std::vector<std::shared_ptr<TrackPiece>>& get_track_pieces() const;

private:
    const std::vector<std::shared_ptr<TrackPiece>> track_pieces_;
};