# gte:167772160 ,lte:201326592， 翻译为版本号

def convert_to_version(num):
    # 拆分为 A.B.C.D
    A = (num >> 24) & 0xFF
    B = (num >> 16) & 0xFF
    C = (num >> 8) & 0xFF
    D = num & 0xFF
    return f"{A}.{B}.{C}.{D}"

# 范围转换
gte = 167772160
lte = 201326592

print("gte:", convert_to_version(gte))
print("lte:", convert_to_version(lte))