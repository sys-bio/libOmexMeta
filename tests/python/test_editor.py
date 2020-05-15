import os
import site
import unittest

test_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
proj_dir = os.path.dirname(test_dir)
src_dir = os.path.join(proj_dir, "src")
pysemsem_dir = os.path.join(src_dir, "pysemsim")

site.addsitedir(src_dir)


class EditorTests(unittest.TestCase):

    def test(self):
        pass
