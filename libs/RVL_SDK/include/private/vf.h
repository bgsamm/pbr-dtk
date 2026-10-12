// From doldecomp/ogws (CC0), include/revolution/VF.h
#ifndef RVL_SDK_PUBLIC_VF_H
#define RVL_SDK_PUBLIC_VF_H
#ifdef __cplusplus
extern "C" {
#endif

#define SWAP16(x) (((x) >> 8) & 0xFF) | (((x) << 8) & 0xFF00)
#define SWAP32(x) ((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24)

#include <private/vf/vf_struct.h>

#include <private/vf/pf_clib.h>
#include <private/vf/pf_code.h>
#include <private/vf/pf_service.h>
#include <private/vf/pf_str.h>
#include <private/vf/pf_w_clib.h>
#include <private/vf/pf_driver.h>
#include <private/vf/pdm_bpb.h>
#include <private/vf/pdm_disk.h>
#include <private/vf/pdm_partition.h>
#include <private/vf/pdm_mbr.h>
#include <private/vf/pdm_dskmng.h>
#include <private/vf/pf_cache.h>
#include <private/vf/pf_cluster.h>
#include <private/vf/pf_dir.h>
#include <private/vf/pf_entry.h>
#include <private/vf/pf_entry_iterator.h>
#include <private/vf/pf_fat.h>
#include <private/vf/pf_fat12.h>
#include <private/vf/pf_fat16.h>
#include <private/vf/pf_fat32.h>
#include <private/vf/pf_fatfs.h>
#include <private/vf/pf_file.h>
#include <private/vf/pf_path.h>
#include <private/vf/pf_sector.h>
#include <private/vf/pf_volume.h>
#include <private/vf/pf_cp932.h>
#include <private/vf/pf_api_util.h>
#include <private/vf/pf_attach.h>
#include <private/vf/pf_detach.h>
#include <private/vf/pf_errnum.h>
#include <private/vf/pf_fclose.h>
#include <private/vf/pf_finfo.h>
#include <private/vf/pf_fopen.h>
#include <private/vf/pf_fread.h>
#include <private/vf/pf_fseek.h>
#include <private/vf/pf_fwrite.h>
#include <private/vf/pf_getdev.h>
#include <private/vf/pf_init_prfile2.h>
#include <private/vf/pf_remove.h>
#include <private/vf/pf_unmount.h>
#include <private/vf/pf_filelock.h>
#include <private/vf/pf_system.h>
#include <private/vf/d_vf.h>
#include <private/vf/d_vf_sys.h>
#include <private/vf/d_hash.h>
#include <private/vf/d_time.h>
#include <private/vf/d_common.h>
#include <private/vf/nand_drv.h>
#include <private/vf/sd_drv.h>

#ifdef __cplusplus
}
#endif
#endif
