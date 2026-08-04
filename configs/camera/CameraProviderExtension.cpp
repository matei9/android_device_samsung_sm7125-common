#include <stdint.h>
#include <android-base/file.h>

static constexpr const char* FLASH_NODE = "/sys/class/camera/flash/rear_flash";
static const int32_t kLevelToRawValue[] = {0, 1001, 1002, 1004, 1006, 1009};

bool supportsTorchStrengthControlExt() { return true; }
int32_t getTorchDefaultStrengthLevelExt() { return 1; }
int32_t getTorchMaxStrengthLevelExt() { return 5; }

int32_t getTorchStrengthLevelExt() {
    std::string value;
    android::base::ReadFileToString(FLASH_NODE, &value);
    int raw = atoi(value.c_str());
    for (int i = 0; i <= 5; i++) if (kLevelToRawValue[i] == raw) return i;
    return raw > 0 ? 1 : 0;
}

void setTorchStrengthLevelExt(int32_t torchStrength, bool enabled) {
    int level = enabled ? torchStrength : 0;
    if (level < 0) level = 0;
    if (level > 5) level = 5;
    android::base::WriteStringToFile(std::to_string(kLevelToRawValue[level]), FLASH_NODE);
}