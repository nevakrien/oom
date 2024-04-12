const std = @import("std");

const Node = struct {
    next: ?*Node,
    data: [1048576 - @sizeOf(?*Node)]u8,
};

comptime {
    std.debug.assert(@sizeOf(Node) == 1048576);
}

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    var head: ?*Node = null;
    var current: ?*Node = null;
    var nodeCount: usize = 0;
    var leaker: ?*u8 = null; //we have to leak since pointers are more than a byte

    std.debug.print("Allocating memory until a crash...\n", .{});
    while (true) {
        const newNode = allocator.create(Node) catch { //|err| {
            //std.debug.print("Failed to create node, system possibly OOM. Error: {}\n", .{ err });
            while (true) {
                leaker = allocator.create(u8) catch {
                    break;
                };
            }
            break;
        };

        newNode.next = null; // Set next pointer to null after allocation

        if (head == null) {
            head = newNode;
        } else {
            current.?.next = newNode;
        }
        current = newNode;
        nodeCount += 1;

        std.debug.print("\rTotal memory allocated: {d} megabytes ", .{nodeCount});
    }

    // Cleanup, freeing all nodes
    while (head) |node| {
        const next = node.next;
        allocator.destroy(node);
        head = next;
    }
    std.debug.print("Memory has been released.\n", .{});
}
