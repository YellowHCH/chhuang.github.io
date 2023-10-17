from typing import List
import torch

import torch._dynamo.config
import logging

torch._dynamo.config.log_level = logging.INFO
torch._dynamo.config.log_level = logging.DEBUG
torch._dynamo.config.output_code = True

torch._dynamo.config.dynamic_shapes = True


def foo_a(a):
    return a * 3

def foo_b(a):
    b = a * 4
    if b.sum() > 0:
        b = b - 5
    else:
        b = b + 6
    return b


@torch.compile(backend="inductor")
def toy_example_fcall_cf(a, b):
    x = a / (torch.abs(a) + 1)
    x = foo_a(x)
    b = foo_b(b)
    return x * b

for _ in range(1):
    toy_example_fcall_cf(torch.randn(10), torch.abs(torch.randn(10)))
