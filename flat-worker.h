#include <nan.h>
using namespace Nan;
class FlatWorker : public AsyncWorker {
 public:
  FlatWorker(Callback* callback, const char* croppedPath, const char* sourcePath, const char* resultPath)
    : AsyncWorker(callback), croppedPath(croppedPath), sourcePath(sourcePath), resultPath(resultPath) {}
  ~FlatWorker() {}
  void Execute () {}

 private:
  const char* croppedPath;
  const char* sourcePath;
  const char* resultPath;
};
