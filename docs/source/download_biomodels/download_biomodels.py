from bioservices import BioModels
import os
import json


thisDir = os.path.dirname(os.path.abspath(__file__))

s = BioModels()

def get_number_of_curated_models() -> int:
    """Figure out how many curated models there are in biomodels right now"""
    all: dict = s.search("*")
    stats: str = all["facetStats"]  # this is a string. Whaaa?
    json_stats: list = json.loads(stats)
    for item in json_stats:
        for val in item["facetValues"]:
            if val["value"] == "Manually curated":
                return int(val["count"])
    raise ValueError("Somethings not quite right")


def download_biomodels(directory: str, num_per_download = 100):
    """downloads sbml models from the curated section of biomodels

    Biomodels has a strict limit of 100 models per download so in this
    function we have to dance around this fact and compute appropriate
    chunk sizes.

    :param directory: (str) where to put zip files containing num_per_download sbml models
    :param num_per_download: How many sbml models to download at a time.
    :return:
    """
    if num_per_download > 100 :
        raise ValueError("Maximum number of models that can be downloaded at a time is 100")
    total_models = get_number_of_curated_models()
    num_downloads = int(total_models / num_per_download)
    remainder = total_models % num_per_download
    if remainder > 0:
        num_downloads += 1

    filenames = []

    start = 1
    for download_number in range(1, num_downloads + 1):
        if download_number == num_downloads:
            # handle last
            end = total_models + 1 # account for 0 indexed python, 1 indexed biomodels
        else:
            end = (download_number * num_per_download) + 1 # account for 0 indexed python, 1 indexed biomodels
        # do something ...

        fname = os.path.join(directory, f"Biomodels{start}-{end-1}.zip")
        filenames.append(fname)

        if os.path.isfile(fname):
            os.remove(fname)

        biomodels_ids = [f"BIOMD{i:010}" for i in range(start, end)]

        s.search_download(biomodels_ids, output_filename=fname)
        print(f"Biomodels models from id {start} to {end-1} saved to {fname}")

        start = end

    return filenames



if __name__ == "__main__":

    download_biomodels(os.path.join(os.path.dirname(__file__)))



_TEST = False

if _TEST:

    import unittest


    class TestBiomodelsDownload(unittest.TestCase):

        def setUp(self) -> None:
            pass

        def tearDown(self) -> None:
            pass

        def replica_of_download_strategy(self, num_per_download, total_models):
            num_downloads = int(total_models / num_per_download)
            remainder = total_models % num_per_download
            if remainder > 0:
                num_downloads += 1

            results = []

            start = 0
            for download_number in range(1, num_downloads + 1):
                if download_number == num_downloads:
                    # handle last
                    end = total_models
                else:
                    end = download_number * num_per_download
                # do something ...
                results.append((start, end))

                start = end
            return results


        def test_easy_numbers(self):
            actual = self.replica_of_download_strategy(100, 1000)
            expected = [(0, 100), (100, 200), (200, 300), (300, 400), (400, 500), (500, 600), (600, 700), (700, 800), (800, 900), (900, 1000)]
            self.assertListEqual(expected, actual)


        def test_with_remainder(self):
            actual = self.replica_of_download_strategy(100, 1005)
            expected = [(0, 100), (100, 200), (200, 300), (300, 400), (400, 500), (500, 600), (600, 700), (700, 800), (800, 900), (900, 1000), (1000, 1005)]
            self.assertListEqual(expected, actual)



