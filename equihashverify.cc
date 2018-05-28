#include <nan.h>
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include <vector>

#include "src/equi/equihash.h"

using namespace v8;

const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

bool verifyEH(const char *hdr, const std::vector<unsigned char> &soln, const char *personalizationString, int n, int k, int hdr_size){
    blake2b_state state;
    EhInitialiseState(n, k, &state, personalizationString);

    blake2b_update(&state, (unsigned char*)&hdr[0], hdr_size);

    bool isValid;
    EhIsValidSolution(n, k, &state, soln, isValid);
    return isValid;
}

void Verify(const v8::FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    if (args.Length() < 5) {
        isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments"))
        );
        return;
    }
    if (!args[2]->IsString()) {
        isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Invalid personalization string"))
        );
        return;
    }
    if (!args[3]->IsInt32() || !args[4]->IsInt32() || !args[5]->IsInt32()) {
        isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Invalid equihash parameters"))
        );
        return;
    }
    if (!args[5]->IsInt32()) {
        isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Invalid header size"))
        );
        return;
    }
    
    Local<Object> header = args[0]->ToObject();
    Local<Object> solution = args[1]->ToObject();
    if(!node::Buffer::HasInstance(header) || !node::Buffer::HasInstance(solution)) {
        isolate->ThrowException(
            Exception::TypeError(String::NewFromUtf8(isolate, "Invalid buffer objects."))
        );
        return;
    }

    const char *hdr = node::Buffer::Data(header);
    if(node::Buffer::Length(header) != args[5].As<Uint32>()->Value()) {
        args.GetReturnValue().Set(false);
        return;
    }

    const char *csoln = node::Buffer::Data(solution);
    std::vector<unsigned char> soln(csoln, csoln + node::Buffer::Length(solution));
    
    String::Utf8Value str(args[2]);
    const char* personalizationString = ToCString(str);
    
    bool result = verifyEH(
        hdr,
        soln,
        personalizationString,
        args[3].As<Uint32>()->Value(), // n
        args[4].As<Uint32>()->Value(), // k
        args[5].As<Uint32>()->Value()  // hdr_size
    );
    
    args.GetReturnValue().Set(result);
}

void Init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "verify", Verify);
}

NODE_MODULE(equihashverify, Init)
