use thiserror::Error;

#[derive(Error, Debug)]
pub enum Error {
    #[error("failed to disable ASLR")]
    ASLR,
}

pub fn disable_aslr() -> Result<(), Error> {
    unsafe {
        match naslr_sys::disable_aslr_real() {
            0 => Ok(()),
            _ => Err(Error::ASLR),
        }
    }
}
