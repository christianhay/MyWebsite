document.addEventListener("DOMContentLoaded", function () {
    const lightbox = document.getElementById("lightbox-modal");
    const lightboxImg = document.getElementById("lightbox-img");
    const closeBtn = document.getElementById("lightbox-close");

    // Open Lightbox Function
    function openLightbox(src) {
        lightboxImg.src = src;
        lightbox.style.display = "flex";
    }

    // Close Lightbox Function
    function closeLightbox() {
        lightbox.style.display = "none";
    }

    // Attach function to window so onclick="openLightbox(this.src)" works
    window.openLightbox = openLightbox;

    // Close when clicking the close button
    closeBtn.addEventListener("click", closeLightbox);

    // Close when clicking outside the image
    lightbox.addEventListener("click", function (event) {
        if (event.target === lightbox) {
            closeLightbox();
        }
    });

    // Close when pressing the Escape key
    document.addEventListener("keydown", function (event) {
        if (event.key === "Escape") {
            closeLightbox();
        }
    });
});
