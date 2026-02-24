use rand::Rng;
use rand::thread_rng;
use std::ffi::c_char;
use std::slice;

const ALL_CHARS: &[u8] = b"abcdefghijklmnopqrstuvwxyz\
                           ABCDEFGHIJKLMNOPQRSTUVWXYZ\
                           0123456789\
                           !@#$%^&*()_+-=[]{}|;:',.<>/?";

#[no_mangle]
pub extern "C" fn ps_generate_password(
    length: i32,
    out_buffer: *mut c_char,
    out_buffer_len: usize,
) -> i32 {
    if length <= 0 {
        return 1;
    }

    if out_buffer.is_null() {
        return 2;
    }

    let length = length as usize;
    if out_buffer_len < length + 1 {
        return 3;
    }

    let mut rng = thread_rng();
    let output = unsafe { slice::from_raw_parts_mut(out_buffer as *mut u8, out_buffer_len) };

    for ch in output.iter_mut().take(length) {
        let idx = rng.gen_range(0..ALL_CHARS.len());
        *ch = ALL_CHARS[idx];
    }

    output[length] = 0;
    0
}
