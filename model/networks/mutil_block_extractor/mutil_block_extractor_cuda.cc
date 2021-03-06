#include <ATen/ATen.h>
#include <torch/torch.h>

#include "mutil_block_extractor_kernel.cuh"
int block_extractor_cuda_forward(
    at::Tensor& source_a,
    at::Tensor& source_b,
    at::Tensor& source_c,
    at::Tensor& flow_field_a, 
    at::Tensor& flow_field_b, 
    at::Tensor& flow_field_c, 
    at::Tensor& masks_a,
    at::Tensor& masks_b,
    at::Tensor& masks_c,
    at::Tensor& output,
    int kernel_size) {
        block_extractor_kernel_forward(source_a, source_b, source_c, flow_field_a, flow_field_b, flow_field_c, masks_a, masks_b, masks_c, output, kernel_size);
    return 1;
}

int block_extractor_cuda_backward(
    at::Tensor& source_a,
    at::Tensor& source_b, 
    at::Tensor& source_c, 
    at::Tensor& flow_field_a,
    at::Tensor& flow_field_b,
    at::Tensor& flow_field_c,
    at::Tensor& masks_a,
    at::Tensor& masks_b,
    at::Tensor& masks_c,
    at::Tensor& grad_output,
    at::Tensor& grad_source_a, 
    at::Tensor& grad_source_b, 
    at::Tensor& grad_source_c, 
    at::Tensor& grad_flow_field_a, 
    at::Tensor& grad_flow_field_b,
    at::Tensor& grad_flow_field_c,
    int kernel_size) {
        block_extractor_kernel_backward(source_a, source_b, source_c, flow_field_a, flow_field_b, flow_field_c, masks_a, masks_b, masks_c, grad_output,
                                 grad_source_a, grad_source_b, grad_source_c, grad_flow_field_a, grad_flow_field_b, grad_flow_field_c,
                                 kernel_size);
    return 1;
}




PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("forward", &block_extractor_cuda_forward, "BlockExtractor forward (CUDA)");
  m.def("backward", &block_extractor_cuda_backward, "BlockExtractor backward (CUDA)");
}
