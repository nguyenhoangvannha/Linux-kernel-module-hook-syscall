#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x10289b50, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x269b90e3, __VMLINUX_SYMBOL_STR(pv_cpu_ops) },
	{ 0x268cc6a2, __VMLINUX_SYMBOL_STR(sys_close) },
	{ 0xf7d9209, __VMLINUX_SYMBOL_STR(__x86_indirect_thunk_eax) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x9b0c73a0, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5AF303E9811213B1173994F");
