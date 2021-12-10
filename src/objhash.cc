#include <nan.h>

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    info.GetReturnValue().Set(Nan::Undefined());
  } else if (info[0]->IsObject()) {
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    obj->Set(
      context,
      Nan::New("msg").ToLocalChecked(),
      info[0]->ToObject(context).ToLocalChecked()
    );
    int hash = obj->GetIdentityHash();

    info.GetReturnValue().Set(Nan::New(hash));
  } else {
    info.GetReturnValue().Set(info[0]);
  }
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(
    context,
    Nan::New("ident").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(Method)->GetFunction(context).ToLocalChecked()
  );
}

NODE_MODULE(objhash, Init)
