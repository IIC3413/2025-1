#pragma once

#include <cstdint>

class FileId {
public:
  static constexpr int UNASSIGNED = INT32_MAX;

  int fd;
  int internal_id;

  FileId(int fd, int internal_id)
      : fd(fd), internal_id(internal_id) {}

  bool operator<(const FileId other) const {
    return this->fd < other.fd;
  }

  bool operator==(const FileId other) const {
    return this->fd == other.fd;
  }
};
