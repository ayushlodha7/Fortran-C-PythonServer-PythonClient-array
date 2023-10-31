module c_interface
  use, intrinsic :: iso_c_binding

  implicit none

  interface
     function send_http_request() bind(C, name="send_http_request")
        import :: c_int
        integer(c_int) :: send_http_request
     end function

     function send_float_array(arr, n) bind(C, name="send_float_array")
        import :: c_int, c_float
        real(c_float), intent(in) :: arr(*)
        integer(c_int), value, intent(in) :: n
        integer(c_int) :: send_float_array
     end function
  end interface

end module c_interface

program fortran_client
  use c_interface
  implicit none

  integer :: status
  real, dimension(5) :: arr = [1.1, 2.2, 3.3, 4.4, 5.5]

  ! Send simple HTTP request
  status = send_http_request()
  if (status /= 0) then
     print *, "Failed to send HTTP request"
     stop
  end if

  ! Send float array
  status = send_float_array(arr, size(arr))
  if (status /= 0) then
     print *, "Failed to send float array"
     stop
  end if

  print *, "Done!"

end program fortran_client
