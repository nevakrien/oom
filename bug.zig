const std = @import("std");
const windows = std.os.windows;

pub fn main() !void {
    const allocation_size = 10 * 1024 * 1024; // Allocate 10 megabytes at a time
    var total_requested: usize = 0;

    while (true) {
        const block = windows.VirtualAlloc(null, allocation_size, windows.MEM_COMMIT | windows.MEM_RESERVE, windows.PAGE_READWRITE) catch {
            std.debug.print("\nVirtualAlloc failed\n", .{});
            break;
        };

        total_requested += allocation_size;
        std.debug.print("\rRequested {d} bytes so far", .{total_requested});

        //use memory so the os dosent optimize it away and zig dosent complain  
        const byte_ptr:*[1]u8 = @ptrCast( block); 
        @memset(byte_ptr, 0xFF,); 
    }

    // chek we are not crashing
    std.debug.print("\nMaximum allocation reached didnt crash can handle...\n", .{});
}
