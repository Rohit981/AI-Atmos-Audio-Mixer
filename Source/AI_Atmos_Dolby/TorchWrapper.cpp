//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "TorchWrapper.h"
//THIRD_PARTY_INCLUDES_START
//#define NOMINMAX
//#include "Windows/AllowWindowsPlatformTypes.h"
//#include <torch/script.h>
//#include <torch/torch.h>
//#include "Windows/HideWindowsPlatformTypes.h"
//THIRD_PARTY_INCLUDES_END
//#include <memory>
//
//TorchWrapper::TorchWrapper(const string& modelPath)
//{
//	try
//	{
//		auto module = make_shared<torch::jit::script::Module>(torch::jit::load(modelPath));
//		Model = new shared_ptr<torch::jit::script::Module>(module);
//		UE_LOG(LogTemp, Warning, TEXT("Torch model loaded successfully from %s"), *FString(modelPath.c_str()));
//	}
//	catch (const c10::Error& e)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Error loading Torch model: %s"), *FString(e.what()));
//	}
//}
//
//TorchWrapper::~TorchWrapper()
//{
//	delete reinterpret_cast<shared_ptr<torch::jit::script::Module>*>(Model);
//}
//
//vector<float> TorchWrapper::RunInference(const vector<float>& inputData)
//{
//	auto module = *reinterpret_cast<shared_ptr<torch::jit::script::Module>*>(Model);
//
//	torch::Tensor inputTensor = torch::from_blob((void*)inputData.data(), {(long)inputData.size() });
//	inputTensor = inputTensor.unsqueeze(0);
//
//	torch::Tensor outputTensor = module->forward({ inputTensor }).toTensor();
//	vector<float> outputData(outputTensor.data_ptr<float>(), outputTensor.data_ptr<float>() + outputTensor.numel());
//
//	return outputData;
//}
