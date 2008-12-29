#include <mln/essential/2d.hh>
int main()
{
  using namespace mln;
  using value::rgb8;
  using value::label_8;


  // \{
  bool vals[6][5] = {
      {0, 1, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 0, 1, 0},
      {1, 0, 1, 1, 1},
      {1, 0, 0, 0, 0}
  };
  image2d<bool> ima = make::image(vals);
  // \}

  // Find and label the different components.
  // Fill the sites of component 2 with red.
  // \{
  label_8 nlabels;
  image2d<label_8> lab = labeling::blobs(ima, c4(), nlabels);

  image2d<rgb8> ima2;
  initialize(ima2, ima);
  data::fill(ima2, literal::black);

  data::fill((ima2 | (pw::value(lab) == pw::cst(2u))).rw(), literal::red);
  // \}
}
