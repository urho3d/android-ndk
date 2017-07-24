"""Test format for the NDK tests."""
import os

import libcxx.android.test.format
import lit.util  # pylint: disable=import-error


def prune_xfails(test):
    """Removes most xfail handling from tests.

    We need to keep some xfail handling because some tests in libc++ that
    really should be using REQUIRES actually used XFAIL (i.e. `XFAIL: c++11`).
    """
    test.xfails = [x for x in test.xfails if x.startswith('c++')]


class TestFormat(libcxx.android.test.format.TestFormat):
    """Loose wrapper around the Android format that disables XFAIL handling."""

    def _evaluate_pass_test(self, test, tmp_base, lit_config):
        """Clears the test's xfail list before delegating to the parent."""
        prune_xfails(test)
        return super(TestFormat, self)._evaluate_pass_test(
            test, tmp_base, lit_config)

    def _evaluate_fail_test(self, test):
        """Clears the test's xfail list before delegating to the parent."""
        prune_xfails(test)
        return super(TestFormat, self)._evaluate_fail_test(test)

    def _clean(self, exec_path):
        exec_file = os.path.basename(exec_path)
        if not self.build_only:
            device_path = self._working_directory(exec_file)
            cmd = ['adb', 'shell', 'rm', '-r', device_path]
            lit.util.executeCommand(cmd)
        try:
            os.remove(exec_path)
        except OSError:
            pass
