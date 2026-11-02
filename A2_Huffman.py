
import heapq

# Node class for Huffman Tree
class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


# Build Huffman Tree using Greedy Strategy
def build_huffman_tree(text):
    frequency = {}

    # Calculate frequency of each character
    for char in text:
        frequency[char] = frequency.get(char, 0) + 1

    # Create a min heap
    heap = []

    for char, freq in frequency.items():
        heapq.heappush(heap, Node(char, freq))

    # Combine two nodes with smallest frequencies
    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)

        new_node = Node(None, left.freq + right.freq)
        new_node.left = left
        new_node.right = right

        heapq.heappush(heap, new_node)

    return heap[0], frequency


# Generate Huffman Codes
def generate_codes(root, code, huffman_codes):
    if root is None:
        return

    if root.char is not None:
        huffman_codes[root.char] = code if code else "0"
        return

    generate_codes(root.left, code + "0", huffman_codes)
    generate_codes(root.right, code + "1", huffman_codes)


# Main Program
text = input("Enter a string: ")

if not text:
    print("Please enter a non-empty string.")
else:
    root, frequency = build_huffman_tree(text)

    huffman_codes = {}
    generate_codes(root, "", huffman_codes)

    print("\nCharacter Frequencies:")
    for char, freq in frequency.items():
        print(repr(char), ":", freq)

    print("\nHuffman Codes:")
    for char, code in huffman_codes.items():
        print(repr(char), ":", code)

    encoded_text = "".join(huffman_codes[char] for char in text)

    print("\nEncoded String:")
    print(encoded_text)
